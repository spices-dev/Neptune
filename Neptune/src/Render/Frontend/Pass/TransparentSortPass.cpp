/**
* @file TransparentSortPass.cpp.
* @brief The TransparentSortPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "TransparentSortPass.h"
#include "Device/Graphics/Frontend/RHI/Pipeline.h"
#include "Device/Graphics/Frontend/RHI/DescriptorList.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"
#include "Resource/Shader/Shader.h"
#include "Resource/Buffer/Buffer.h"
#include "Resource/ResourcePool/ResourcePool.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"
#include "World/Component/SOPComponent.h"
#include "Asset/SOP/GS3D.h"
#include "Resource/Texture/RenderTarget.h"

namespace Neptune::Render {

	using namespace Graphic;

	namespace {
		
		constexpr uint32_t kTileSize            = 16;
		constexpr uint32_t kMaxGaussians        = 18000000;
		constexpr uint32_t kAvgTilesPerGaussian = 6;
		constexpr uint32_t kMaxInstances        = kMaxGaussians * kAvgTilesPerGaussian;
		constexpr uint32_t kMaxInstanceNumWG    = (kMaxInstances + 255u) / 256u;
		constexpr uint32_t kMaxTilesX           = (3840u + kTileSize - 1u) / kTileSize;
		constexpr uint32_t kMaxTilesY           = (2160u + kTileSize - 1u) / kTileSize;
		constexpr uint32_t kMaxTiles            = kMaxTilesX * kMaxTilesY;
		
		struct PreProcessPush
		{
			uint64_t splatAddress;
			uint64_t entryAddress;
			uint64_t infoAddress;
			uint32_t gsCount;
			uint32_t tilesX;
			uint32_t tilesY;
			uint32_t maxInstances;
		};

		struct SetupPush
		{
			uint64_t infoAddress;
			uint32_t maxInstances;
		};

		struct RadixPush
		{
			uint64_t srcAddress;
			uint64_t dstAddress;
			uint64_t histAddress;
			uint64_t infoAddress;
			uint32_t shift;
		};

		struct RangePush
		{
			uint64_t sortedAddress;
			uint64_t rangeAddress;
			uint64_t infoAddress;
		};

		struct TileRenderPush
		{
			uint64_t splatAddress;
			uint64_t sortedAddress;
			uint64_t rangeAddress;
			uint32_t tilesX;
			uint32_t width;
			uint32_t height;
		};
	}
	
	void TransparentSortPass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE

		auto& bufferPool       = ResourcePool<Buffer>::Instance();
		auto& shaderPool       = ResourcePool<Shader>::Instance();
		auto& renderTargetPool = ResourcePool<RenderTarget>::Instance();
		
		{
			RenderTargetCreateInfo    info{};
			info.format             = TextureFormat::RGBA16_SFLOAT;
			info.domain             = TextureDomain::Texture2D;
			info.width              = m_RTSize.x;
			info.height             = m_RTSize.y;
			info.usage.Set(Graphic::EImageUsage::Storage);
			info.usage.Set(Graphic::EImageUsage::TransferSrc);
			
			auto GS3DScene = CreateSP<RenderTarget>(info);

			renderTargetPool.Registry("GS3DScene", GS3DScene);
		}
		
		{
			auto MakeBuffer = [&](InFlightResource<RHI::Buffer>& slot, const std::string& base, uint64_t bytes, const Container::BitSet<EBufferUsage>& usage = {})
			{
				for (int i = 0; i < MaxFrameInFlight; ++i)
				{
					std::stringstream ss;
					ss << base << "_" << i;

					if (!bufferPool.Has(ss.str()))
					{
						auto s = bufferPool.Load<Buffer>(ss.str(), BufferCreateInfo{ bytes, usage });
						s->GetRHIResource()->SetName(ss.str());
					}

					slot.Get(i) = bufferPool.Access(ss.str())->GetRHIResource();
				}
			};

			MakeBuffer(m_SplatBuffer,  "TileSplatBuffer",  uint64_t(kMaxGaussians) * 32ull);
			MakeBuffer(m_EntryBufferA, "TileEntryBufferA", uint64_t(kMaxInstances) * sizeof(uint64_t));
			MakeBuffer(m_EntryBufferB, "TileEntryBufferB", uint64_t(kMaxInstances) * sizeof(uint64_t));
			MakeBuffer(m_HistBuffer,   "TileHistBuffer",   (256ull * kMaxInstanceNumWG + 256ull) * sizeof(uint32_t));
			MakeBuffer(m_RangeBuffer,  "TileRangeBuffer",  uint64_t(kMaxTiles) * sizeof(uint32_t) * 2ull, Container::BitSet(EBufferUsage::TransferDst));
			MakeBuffer(m_InfoBuffer,   "TileSortInfoBuffer", 24ull, Container::BitSet<EBufferUsage>(EBufferUsage::Indirect, EBufferUsage::TransferDst) );
		}

		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_PreProcessDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_PreProcessDescriptorList.Get(i)->AddShaderConstant(sizeof(PreProcessPush));
				m_PreProcessDescriptorList.Get(i)->AddUniformBuffer(1, 0, sizeof(uint64_t));
				m_PreProcessDescriptorList.Get(i)->CombineSharedLayout();
				m_PreProcessDescriptorList.Get(i)->Build();
			}

			m_PreProcessPipeline = CreateSP<RHI::Pipeline>();
			m_PreProcessPipeline->SetDefault();
			m_PreProcessPipeline->SetDescriptorList(m_PreProcessDescriptorList.Get(0));

			if (!shaderPool.Has("TileRenderPreprocess"))
			{
				auto s = shaderPool.Load<Shader>("TileRenderPreprocess");
				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TileRenderPreprocess.comp.spv");
			}

			auto shader = shaderPool.Access("TileRenderPreprocess");
			m_PreProcessPipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
			m_PreProcessPipeline->BuildComputePipeline();
		}

		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_SetupDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_SetupDescriptorList.Get(i)->AddShaderConstant(sizeof(SetupPush));
				m_SetupDescriptorList.Get(i)->CombineSharedLayout();
				m_SetupDescriptorList.Get(i)->Build();
			}

			m_SetupPipeline = CreateSP<RHI::Pipeline>();
			m_SetupPipeline->SetDefault();
			m_SetupPipeline->SetDescriptorList(m_SetupDescriptorList.Get(0));

			if (!shaderPool.Has("TileRenderSortSetup"))
			{
				auto s = shaderPool.Load<Shader>("TileRenderSortSetup");
				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TileRenderSortSetup.comp.spv");
			}

			auto shader = shaderPool.Access("TileRenderSortSetup");
			m_SetupPipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
			m_SetupPipeline->BuildComputePipeline();
		}
		
		{
			auto BuildRadixStage = [&](InFlightResource<RHI::DescriptorList>& descList,
										SP<RHI::Pipeline>& pipeline,
										const char* shaderName,
										const char* spvPath)
			{
				for (int i = 0; i < MaxFrameInFlight; ++i)
				{
					descList.Get(i) = CreateSP<RHI::DescriptorList>();
					descList.Get(i)->AddShaderConstant(sizeof(RadixPush));
					descList.Get(i)->CombineSharedLayout();
					descList.Get(i)->Build();
				}

				pipeline = CreateSP<RHI::Pipeline>();
				pipeline->SetDefault();
				pipeline->SetDescriptorList(descList.Get(0));

				if (!shaderPool.Has(shaderName))
				{
					auto s = shaderPool.Load<Shader>(shaderName);
					s->SetStage(ShaderStage::Compute);
					s->SetSource(spvPath);
				}

				auto shader = shaderPool.Access(shaderName);
				pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
				pipeline->BuildComputePipeline();
			};

			BuildRadixStage(m_HistogramDescriptorList, m_HistogramPipeline,
							 "TransparentSortPassRadixHistogram", "Shaders/src/TransparentSortPassRadixHistogram.comp.spv");

			BuildRadixStage(m_ScanDescriptorList, m_ScanPipeline,
							 "TransparentSortPassRadixScan", "Shaders/src/TransparentSortPassRadixScan.comp.spv");

			BuildRadixStage(m_ScatterDescriptorList, m_ScatterPipeline,
							 "TransparentSortPassRadixScatter", "Shaders/src/TransparentSortPassRadixScatter.comp.spv");
		}
		
		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_RangeDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_RangeDescriptorList.Get(i)->AddShaderConstant(sizeof(RangePush));
				m_RangeDescriptorList.Get(i)->CombineSharedLayout();
				m_RangeDescriptorList.Get(i)->Build();
			}

			m_RangePipeline = CreateSP<RHI::Pipeline>();
			m_RangePipeline->SetDefault();
			m_RangePipeline->SetDescriptorList(m_RangeDescriptorList.Get(0));

			if (!shaderPool.Has("TileRenderRanges"))
			{
				auto s = shaderPool.Load<Shader>("TileRenderRanges");
				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TileRenderRanges.comp.spv");
			}

			auto shader = shaderPool.Access("TileRenderRanges");
			m_RangePipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
			m_RangePipeline->BuildComputePipeline();
		}
		
		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_TileRenderDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_TileRenderDescriptorList.Get(i)->AddShaderConstant(sizeof(TileRenderPush));
				m_TileRenderDescriptorList.Get(i)->AddStorageTexture(1, 0, ResourcePool<RenderTarget>::Instance().Access("GS3DScene")->GetRHIResource());

				m_TileRenderDescriptorList.Get(i)->CombineSharedLayout();
				m_TileRenderDescriptorList.Get(i)->Build();
			}

			m_TileRenderPipeline = CreateSP<RHI::Pipeline>();
			m_TileRenderPipeline->SetDefault();
			m_TileRenderPipeline->SetDescriptorList(m_TileRenderDescriptorList.Get(0));

			if (!shaderPool.Has("TileRender"))
			{
				auto s = shaderPool.Load<Shader>("TileRender");
				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TileRender.comp.spv");
			}

			auto shader = shaderPool.Access("TileRender");
			m_TileRenderPipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
			m_TileRenderPipeline->BuildComputePipeline();
		}
	}

	void TransparentSortPass::OnCollectRHI(Scene* scene)
	{
		NEPTUNE_PROFILE_ZONE

		SP<SOP::GS3D> item = nullptr;
		
		scene->ViewComponent<SOPComponent>([&](auto e, auto& component) {
			
			if (auto p = std::dynamic_pointer_cast<SOP::GS3D>(component.GetModel()))
			{
				item = p;
				return true;
			}
			
			return false;
		});

		if (!item) return;

		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();
		
		uint32_t gsCount = item->GetPointCount();
		assert(gsCount <= kMaxGaussians);
		
		uint32_t width  = static_cast<uint32_t>(m_RTSize.x);
		uint32_t height = static_cast<uint32_t>(m_RTSize.y);
		uint32_t tilesX = (width  + kTileSize - 1u) / kTileSize;
		uint32_t tilesY = (height + kTileSize - 1u) / kTileSize;
		assert(tilesX <= kMaxTilesX && tilesY <= kMaxTilesY);
		
		uint32_t frame = clock.m_FrameIndex;
		
		uint64_t splatAddr  = m_SplatBuffer.Get(frame)->GetDeviceAddress();
		uint64_t entryAAddr = m_EntryBufferA.Get(frame)->GetDeviceAddress();
		uint64_t entryBAddr = m_EntryBufferB.Get(frame)->GetDeviceAddress();
		uint64_t histAddr   = m_HistBuffer.Get(frame)->GetDeviceAddress();
		uint64_t infoAddr   = m_InfoBuffer.Get(frame)->GetDeviceAddress();
		uint64_t rangeAddr  = m_RangeBuffer.Get(frame)->GetDeviceAddress();
		
		MemoryBarrierDesc       barrier{};
		barrier.srcAccess     = EPipelineAccess::ShaderWrite;
		barrier.dstAccess     = EPipelineAccess::ShaderRead; //| EPipelineAccess::ShaderWrite;
		barrier.srcStage      = EPipelineStage::ComputeShader;
		barrier.dstStage      = EPipelineStage::ComputeShader;
		
		RHI::CmdList cmdList;

		cmdList.SetComputeCmdList(clock);
		
		cmdList.CmdFillBuffer(m_InfoBuffer.Get(frame), 0, sizeof(uint32_t), 0u);
		
		cmdList.CmdFillBuffer(m_RangeBuffer.Get(frame), 0, uint64_t(kMaxTiles) * 8ull, 0u);
		
		cmdList.CmdInsertBarrier(barrier);
		
		{
			PreProcessPush                 push{};
			push.splatAddress            = splatAddr;
			push.entryAddress            = entryAAddr;
			push.infoAddress             = infoAddr;
			push.gsCount                 = gsCount;
			push.tilesX                  = tilesX;
			push.tilesY                  = tilesY;
			push.maxInstances            = kMaxInstances;
			
			m_PreProcessDescriptorList.Get(frame)->UpdateUniformBuffer(1, 0, &item->GetDescDeviceAddress());
			
			cmdList.CmdBindPipeline(m_PreProcessPipeline);

			cmdList.CmdBindDescriptor(m_PreProcessDescriptorList.Get(frame));
			
			cmdList.CmdUpdateShaderConstant(&push, sizeof(push));
			
			cmdList.CmdDispatch((gsCount + 255u) / 256u, 1, 1);

			cmdList.CmdInsertBarrier(barrier);
		}
		
		{
			SetupPush                push{};
			push.infoAddress       = infoAddr;
			push.maxInstances      = kMaxInstances;
			
			cmdList.CmdBindPipeline(m_SetupPipeline);

			cmdList.CmdBindDescriptor(m_SetupDescriptorList.Get(frame));
			
			cmdList.CmdUpdateShaderConstant(&push, sizeof(push));
			
			cmdList.CmdDispatch(1, 1, 1);
			
			cmdList.CmdInsertBarrier(barrier);
		}
		
		{
			RadixPush                  push{};
			push.srcAddress          = entryAAddr;
			push.dstAddress          = entryBAddr;
			push.histAddress         = histAddr;
			push.infoAddress         = infoAddr;
			
			for (int pass = 0; pass < 4; ++pass) 
			{
				push.shift = 25u + 8u * static_cast<uint32_t>(pass);

				cmdList.CmdBindPipeline(m_HistogramPipeline);

				cmdList.CmdBindDescriptor(m_HistogramDescriptorList.Get(frame));
				
				cmdList.CmdUpdateShaderConstant(&push, sizeof(push));
			
				cmdList.CmdDispatchIndirect(m_InfoBuffer.Get(frame), 12);
			
				cmdList.CmdInsertBarrier(barrier);
			
				cmdList.CmdBindPipeline(m_ScanPipeline);

				cmdList.CmdBindDescriptor(m_ScanDescriptorList.Get(frame));
				
				cmdList.CmdUpdateShaderConstant(&push, sizeof(push));
				
				cmdList.CmdDispatch(256, 1, 1);
			
				cmdList.CmdInsertBarrier(barrier);

				cmdList.CmdBindPipeline(m_ScatterPipeline);

				cmdList.CmdBindDescriptor(m_ScatterDescriptorList.Get(clock.m_FrameIndex));
				
				cmdList.CmdUpdateShaderConstant(&push, sizeof(push));

				cmdList.CmdDispatchIndirect(m_InfoBuffer.Get(frame), 12);
			
				cmdList.CmdInsertBarrier(barrier);

				std::swap(push.srcAddress, push.dstAddress);
			}
			
			uint64_t sortedAddr = push.srcAddress;
			
			{
				RangePush                 rpush{};
				rpush.sortedAddress     = sortedAddr;
				rpush.rangeAddress      = rangeAddr;
				rpush.infoAddress       = infoAddr;

				cmdList.CmdBindPipeline(m_RangePipeline);
				
				cmdList.CmdBindDescriptor(m_RangeDescriptorList.Get(frame));
				
				cmdList.CmdUpdateShaderConstant(&rpush, sizeof(rpush));
				
				cmdList.CmdDispatchIndirect(m_InfoBuffer.Get(frame), 12);
				
				cmdList.CmdInsertBarrier(barrier);
			}
			
			{
				TileRenderPush               tpush{};
				tpush.splatAddress         = splatAddr;
				tpush.sortedAddress        = sortedAddr;
				tpush.rangeAddress         = rangeAddr;
				tpush.tilesX               = tilesX;
				tpush.width                = width;
				tpush.height               = height;

				m_TileRenderDescriptorList.Get(frame)->UpdateStorageTexture(1, 0, ResourcePool<RenderTarget>::Instance().Access("GS3DScene")->GetRHIResource());
				
				cmdList.CmdBindPipeline(m_TileRenderPipeline);
				
				cmdList.CmdBindDescriptor(m_TileRenderDescriptorList.Get(frame));
				
				cmdList.CmdUpdateShaderConstant(&tpush, sizeof(tpush));
				
				cmdList.CmdDispatch(tilesX, tilesY, 1);
			}
		}
	}

}
