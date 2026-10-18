/**
* @file GS3DTileRenderPass.cpp.
* @brief The GS3DTileRenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "GS3DTileRenderPass.h"
#include "Header/GS3DTileRenderCore.h"
#include "Device/Graphics/Frontend/RHI/Pipeline.h"
#include "Device/Graphics/Frontend/RHI/DescriptorList.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"
#include "Device/Graphics/Frontend/RHI/RenderTarget.h"
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
	using namespace ShaderCore::GS3DTileRenderCore;
	
	void GS3DTileRenderPass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE
		
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
			info.usage.Set(Graphic::EImageUsage::Sampler);
			
			for (uint32_t i = 0; i < MaxFrameInFlight; ++i)
			{
				auto GS3DScene = CreateSP<RenderTarget>(info);
				
				renderTargetPool.Registry("GS3DScene_" + i, GS3DScene);
				
				GS3DScene->SetName("GS3DScene_" + i);
			}
		}
		
		{
			auto MakeBuffer = [&](InFlightResource<RHI::Buffer>& slot, const std::string& base, uint64_t bytes, const Container::BitSet<EBufferUsage>& usage = {})
			{
				for (uint32_t i = 0; i < MaxFrameInFlight; ++i)
				{
					std::stringstream ss;
					ss << base << "_" << i;

					slot.Get(i) = CreateSP<RHI::Buffer>();
					
					slot.Get(i)->CreateBuffer(BufferCreateInfo{ bytes, usage });
					
					slot.Get(i)->SetName(ss.str());
				}
			};

			MakeBuffer(m_SplatBuffer,  "TileSplatBuffer",  static_cast<uint64_t>(MAXGAUSSIANS) * sizeof(Splat));
			MakeBuffer(m_EntryBufferA, "TileEntryBufferA", static_cast<uint64_t>(MAXTILEGAUSSIANS) * sizeof(uint64_t));
			MakeBuffer(m_EntryBufferB, "TileEntryBufferB", static_cast<uint64_t>(MAXTILEGAUSSIANS) * sizeof(uint64_t));
			MakeBuffer(m_HistBuffer,   "TileHistBuffer",   (256ull * MAXTILEGAUSSIANSNUMWG + 256ull) * sizeof(uint32_t));
			MakeBuffer(m_RangeBuffer,  "TileRangeBuffer",  static_cast<uint64_t>(MAXTILES) * sizeof(uint32_t) * 2ull, EBufferUsage::TransferDst);
			MakeBuffer(m_InfoBuffer,   "TileSortInfoBuffer", sizeof(TileSortInfo), { EBufferUsage::Indirect, EBufferUsage::TransferDst} );
		}

		{
			for (uint32_t i = 0; i < MaxFrameInFlight; ++i)
			{
				m_PreProcessDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_PreProcessDescriptorList.Get(i)->AddShaderConstant(sizeof(PreProcessPush));
				m_PreProcessDescriptorList.Get(i)->AddUniformTexture(1, 0, ResourcePool<RenderTarget>::Instance().Access("CurrDecodeRT")->GetRHIResource());
				m_PreProcessDescriptorList.Get(i)->AddUniformTexture(1, 1, ResourcePool<RenderTarget>::Instance().Access("CurrDecodeRT")->GetRHIResource());
				m_PreProcessDescriptorList.Get(i)->AddUniformTexture(1, 2, ResourcePool<RenderTarget>::Instance().Access("CurrDecodeRT")->GetRHIResource());
				m_PreProcessDescriptorList.Get(i)->AddUniformTexture(1, 3, ResourcePool<RenderTarget>::Instance().Access("CurrDecodeRT")->GetRHIResource());
				m_PreProcessDescriptorList.Get(i)->AddUniformTexture(1, 4, ResourcePool<RenderTarget>::Instance().Access("CurrDecodeRT")->GetRHIResource());
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
			for (uint32_t i = 0; i < MaxFrameInFlight; ++i)
			{
				m_SetupDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_SetupDescriptorList.Get(i)->AddShaderConstant(sizeof(uint64_t));
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
				for (uint32_t i = 0; i < MaxFrameInFlight; ++i)
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
			for (uint32_t i = 0; i < MaxFrameInFlight; ++i)
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
			for (uint32_t i = 0; i < MaxFrameInFlight; ++i)
			{
				m_TileRenderDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_TileRenderDescriptorList.Get(i)->AddShaderConstant(sizeof(TileRenderPush));
				m_TileRenderDescriptorList.Get(i)->AddStorageTexture(1, 0, ResourcePool<RenderTarget>::Instance().Access("GS3DScene_" + i)->GetRHIResource());

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

	void GS3DTileRenderPass::OnCollectRHI(Scene* scene)
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
		assert(gsCount <= MAXGAUSSIANS);
		
		uint32_t width    = static_cast<uint32_t>(m_RTSize.x);
		uint32_t height   = static_cast<uint32_t>(m_RTSize.y);
		uint32_t tilesX   = (width  + TILE_SIZE - 1u) / TILE_SIZE;
		uint32_t tilesY   = (height + TILE_SIZE - 1u) / TILE_SIZE;
		uint32_t numTiles = tilesX * tilesY;
		assert(tilesX <= MAXTILESX && tilesY <= MAXTILESY);
		
		uint32_t frame = clock.m_FrameIndex;
		
		uint64_t splatAddr              = m_SplatBuffer .Get(frame)->GetDeviceAddress();
		uint64_t entryAAddr             = m_EntryBufferA.Get(frame)->GetDeviceAddress();
		uint64_t entryBAddr             = m_EntryBufferB.Get(frame)->GetDeviceAddress();
		uint64_t histAddr               = m_HistBuffer  .Get(frame)->GetDeviceAddress();
		uint64_t infoAddr               = m_InfoBuffer  .Get(frame)->GetDeviceAddress();
		uint64_t rangeAddr              = m_RangeBuffer .Get(frame)->GetDeviceAddress();
		
		MemoryBarrierDesc                 barrier{};
		barrier.srcAccess            = EPipelineAccess::ShaderWrite;
		barrier.dstAccess            = { EPipelineAccess::ShaderRead, EPipelineAccess::ShaderWrite };
		barrier.srcStage             = EPipelineStage::ComputeShader;
		barrier.dstStage             = EPipelineStage::ComputeShader;
		
		RHI::CmdList cmdList;

		cmdList.SetComputeCmdList(clock);
		
		cmdList.CmdFillBuffer(m_InfoBuffer.Get(frame), 0, sizeof(uint32_t), 0);
		
		cmdList.CmdFillBuffer(m_RangeBuffer.Get(frame), 0, static_cast<uint64_t>(MAXTILES) * 8, 0);
		
		{
			m_PreProcessDescriptorList.Get(frame)->UpdateUniformTexture(1, 0, item->GetDesc().means_0->GetRHIResource());
			m_PreProcessDescriptorList.Get(frame)->UpdateUniformTexture(1, 1, item->GetDesc().means_1->GetRHIResource());
			m_PreProcessDescriptorList.Get(frame)->UpdateUniformTexture(1, 2, item->GetDesc().scales->GetRHIResource());
			m_PreProcessDescriptorList.Get(frame)->UpdateUniformTexture(1, 3, item->GetDesc().quats->GetRHIResource());
			m_PreProcessDescriptorList.Get(frame)->UpdateUniformTexture(1, 4, item->GetDesc().sh0->GetRHIResource());
			
			PreProcessPush                   push{};
			push.splatAddress              = splatAddr;
			push.entryAddress              = entryAAddr;
			push.infoAddress               = infoAddr;
			push.descAddress               = item->GetDescDeviceAddress();
			push.gsCount                   = gsCount;
			push.imageWidth                = item->GetDesc().means_0->GetRHIResource()->GetWidth();
			push.tilesX                    = tilesX;
			push.tilesY                    = tilesY;
			
			cmdList.CmdBindPipeline(m_PreProcessPipeline);

			cmdList.CmdBindDescriptor(m_PreProcessDescriptorList.Get(frame));
			
			cmdList.CmdUpdateShaderConstant(&push, sizeof(push));
			
			cmdList.CmdDispatch((gsCount + 255u) / 256u, 1, 1);

			cmdList.CmdInsertBarrier(barrier);
		}
		
		{
			cmdList.CmdBindPipeline(m_SetupPipeline);

			cmdList.CmdBindDescriptor(m_SetupDescriptorList.Get(frame));
			
			cmdList.CmdUpdateShaderConstant(&infoAddr, sizeof(infoAddr));
			
			cmdList.CmdDispatch(1, 1, 1);
			
			cmdList.CmdInsertBarrier(barrier);
			
			MemoryBarrierDesc                  indirectBarrier{};
			indirectBarrier.srcAccess     = EPipelineAccess::ShaderWrite;
			indirectBarrier.dstAccess     = EPipelineAccess::IndirectCommandRead;
			indirectBarrier.srcStage      = EPipelineStage::ComputeShader;
			indirectBarrier.dstStage      = EPipelineStage::DrawIndirect;
			
			cmdList.CmdInsertBarrier(indirectBarrier);
		}
		
		uint64_t sortedAddr = entryAAddr;

		{
			RadixPush                  push{};
			push.srcAddress          = entryAAddr;
			push.dstAddress          = entryBAddr;
			push.histAddress         = histAddr;
			push.infoAddress         = infoAddr;
			
			for (uint32_t pass = 0; pass < RADIX_NUM_PASSES; ++pass)
			{
				push.shift = RADIX_FIRST_BIT + RADIX_DIGITAL_BIT * pass;

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
			
			if constexpr (RADIX_NUM_PASSES % 2 == 1)
			{
				sortedAddr = push.srcAddress;
			}
		}
		
		{
			RangePush                 push{};
			push.sortedAddress      = sortedAddr;
			push.rangeAddress       = rangeAddr;
			push.infoAddress        = infoAddr;
			push.numTiles           = numTiles;

			cmdList.CmdBindPipeline(m_RangePipeline);
			
			cmdList.CmdBindDescriptor(m_RangeDescriptorList.Get(frame));
			
			cmdList.CmdUpdateShaderConstant(&push, sizeof(push));
			
			cmdList.CmdDispatchIndirect(m_InfoBuffer.Get(frame), 12);
			
			cmdList.CmdInsertBarrier(barrier);
		}
		
		{
			auto GS3DScene = ResourcePool<RenderTarget>::Instance().Access("GS3DScene_" + frame)->GetRHIResource();
			
			TileRenderPush               push{};
			push.splatAddress          = splatAddr;
			push.sortedAddress         = sortedAddr;
			push.rangeAddress          = rangeAddr;
			push.sh0CodesAddress       = item->GetDesc().desc.host->at(0).sh0CodesAddress;
			push.tilesX                = tilesX;
			push.width                 = width;
			push.height                = height;

			m_TileRenderDescriptorList.Get(frame)->UpdateStorageTexture(1, 0, GS3DScene);
			
			cmdList.CmdBindPipeline(m_TileRenderPipeline);
			
			cmdList.CmdBindDescriptor(m_TileRenderDescriptorList.Get(frame));
			
			cmdList.CmdUpdateShaderConstant(&push, sizeof(push));
			
			cmdList.CmdDispatch(tilesX, tilesY, 1);
		}
	}

}
