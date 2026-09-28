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

namespace Neptune::Render {

	using namespace Graphic;

	namespace {
		
		constexpr uint32_t kMaxTransparent = 18000000;
		constexpr uint32_t kMaxNumWG       = (kMaxTransparent + 255u) / 256u;
		
		struct Push {
			uint64_t src, dst, hist;
			uint32_t numElements, shift, numWG;
		};
	}
	
	void TransparentSortPass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE

		{
			auto& resourcePool = ResourcePool<Buffer>::Instance();

			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				std::stringstream ss;
				ss << "TransparentSortBufferA_" << i;
				
				if (!resourcePool.Has(ss.str()))
				{
					auto s = resourcePool.Load<Buffer>(ss.str(), BufferCreateInfo{ uint64_t(kMaxTransparent) * sizeof(uint64_t) } );
				
					s->GetRHIResource()->SetName(ss.str());
				}
				
				m_SortBufferA.Get(i) = resourcePool.Access(ss.str())->GetRHIResource();
			}
			
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				std::stringstream ss;
				ss << "TransparentSortBufferB_" << i;
				
				if (!resourcePool.Has(ss.str()))
				{
					auto s = resourcePool.Load<Buffer>(ss.str(), BufferCreateInfo{ uint64_t(kMaxTransparent) * sizeof(uint64_t) } );
				
					s->GetRHIResource()->SetName(ss.str());
				}
				
				m_SortBufferB.Get(i) = resourcePool.Access(ss.str())->GetRHIResource();
			}
			
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				std::stringstream ss;
				ss << "TransparentHistBuffer_" << i;
				
				if (!resourcePool.Has(ss.str()))
				{
					auto s = resourcePool.Load<Buffer>(ss.str(), BufferCreateInfo{ (256ull * kMaxNumWG + 256ull) * sizeof(uint32_t) } );
				
					s->GetRHIResource()->SetName(ss.str());
				}
				
				m_HistBuffer.Get(i) = resourcePool.Access(ss.str())->GetRHIResource();
			}
			
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				std::stringstream ss;
				ss << "TransparentIndirectBuffer_" << i;
				
				if (!resourcePool.Has(ss.str()))
				{
					auto s = resourcePool.Load<Buffer>(ss.str(), BufferCreateInfo{ 16, Graphic::EBufferUsage::Indirect } );
				
					s->GetRHIResource()->SetName(ss.str());
					
					std::array<uint32_t, 4> data { 4, 0, 0, 0 }; 
					
					s->GetRHIResource()->WriteToBuffer(data.data(), 16);
					
					s->GetRHIResource()->Flush();
				}
				
				m_IndirectBuffer.Get(i) = resourcePool.Access(ss.str())->GetRHIResource();
			}
		}
		
		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_KGenDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_KGenDescriptorList.Get(i)->AddShaderConstant(sizeof(uint32_t));
				m_KGenDescriptorList.Get(i)->AddUniformBuffer(1, 0, sizeof(uint64_t));
				m_KGenDescriptorList.Get(i)->AddUniformBuffer(1, 1, sizeof(uint64_t));
				m_KGenDescriptorList.Get(i)->AddUniformBuffer(1, 2, sizeof(uint64_t));
				m_KGenDescriptorList.Get(i)->CombineSharedLayout();
				m_KGenDescriptorList.Get(i)->Build();
			}
			
			m_KGenPipeline = CreateSP<RHI::Pipeline>();
			m_KGenPipeline->SetDefault();
			m_KGenPipeline->SetDescriptorList(m_KGenDescriptorList.Get(0));
			
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("TransparentSortPassKeyGenComp"))
			{
				auto s = resourcePool.Load<Shader>("TransparentSortPassKeyGenComp");

				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TransparentSortPassKeyGenComp.comp.spv");
			}

			auto shader = resourcePool.Access("TransparentSortPassKeyGenComp");

			m_KGenPipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
			
			m_KGenPipeline->BuildComputePipeline();
		}
		
		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_HistogramDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_HistogramDescriptorList.Get(i)->AddShaderConstant(sizeof(Push));
				m_HistogramDescriptorList.Get(i)->CombineSharedLayout();
				m_HistogramDescriptorList.Get(i)->Build();
			}
			
			m_HistogramPipeline = CreateSP<RHI::Pipeline>();
			m_HistogramPipeline->SetDefault();
			m_HistogramPipeline->SetDescriptorList(m_HistogramDescriptorList.Get(0));
			
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("TransparentSortPassRadixHistogram"))
			{
				auto s = resourcePool.Load<Shader>("TransparentSortPassRadixHistogram");

				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TransparentSortPassRadixHistogram.comp.spv");
			}

			auto shader = resourcePool.Access("TransparentSortPassRadixHistogram");

			m_HistogramPipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
			
			m_HistogramPipeline->BuildComputePipeline();
		}

		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_ScanDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_ScanDescriptorList.Get(i)->AddShaderConstant(sizeof(Push));
				m_ScanDescriptorList.Get(i)->CombineSharedLayout();
				m_ScanDescriptorList.Get(i)->Build();
			}
			
			m_ScanPipeline = CreateSP<RHI::Pipeline>();
			m_ScanPipeline->SetDefault();
			m_ScanPipeline->SetDescriptorList(m_ScanDescriptorList.Get(0));
			
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("TransparentSortPassRadixScan"))
			{
				auto s = resourcePool.Load<Shader>("TransparentSortPassRadixScan");

				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TransparentSortPassRadixScan.comp.spv");
			}

            auto shader = resourcePool.Access("TransparentSortPassRadixScan");

			m_ScanPipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
			
			m_ScanPipeline->BuildComputePipeline();
		}
		
		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_ScatterDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_ScatterDescriptorList.Get(i)->AddShaderConstant(sizeof(Push));
				m_ScatterDescriptorList.Get(i)->CombineSharedLayout();
				m_ScatterDescriptorList.Get(i)->Build();
			}

			m_ScatterPipeline = CreateSP<RHI::Pipeline>();
			m_ScatterPipeline->SetDefault();
			m_ScatterPipeline->SetDescriptorList(m_ScatterDescriptorList.Get(0));
					
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("TransparentSortPassRadixScatter"))
			{
				auto s = resourcePool.Load<Shader>("TransparentSortPassRadixScatter");

				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TransparentSortPassRadixScatter.comp.spv");
			}

			auto shader = resourcePool.Access("TransparentSortPassRadixScatter");

			m_ScatterPipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
					
			m_ScatterPipeline->BuildComputePipeline();
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
		
		assert(gsCount <= kMaxTransparent);
		
		uint32_t numWG = (gsCount + 255) / 256;
		
		{
			auto sortBufferAddress = m_SortBufferA.Get(clock.m_FrameIndex)->GetDeviceAddress();
			
			auto indirectBufferAddress = m_IndirectBuffer.Get(clock.m_FrameIndex)->GetDeviceAddress();
		
			m_KGenDescriptorList.Get(clock.m_FrameIndex)->UpdateUniformBuffer(1, 0, &item->GetDescDeviceAddress());
			
			m_KGenDescriptorList.Get(clock.m_FrameIndex)->UpdateUniformBuffer(1, 1, &sortBufferAddress);
			
			m_KGenDescriptorList.Get(clock.m_FrameIndex)->UpdateUniformBuffer(1, 2, &indirectBufferAddress);
			
			RHI::CmdList cmdList;

			cmdList.SetComputeCmdList(clock);

			cmdList.CmdFillBuffer(m_IndirectBuffer.Get(clock.m_FrameIndex), 4, 4, 0);
			
			cmdList.CmdBindPipeline(m_KGenPipeline);

			cmdList.CmdBindDescriptor(m_KGenDescriptorList.Get(clock.m_FrameIndex));
			
			cmdList.CmdUpdateShaderConstant(&gsCount, sizeof(uint32_t));
			
			cmdList.CmdDispatch(numWG, 1, 1);
			
			MemoryBarrierDesc       barrier{};
			barrier.srcAccess     = EPipelineAccess::ShaderWrite;
			barrier.dstAccess     = EPipelineAccess::ShaderRead;
			barrier.srcStage      = EPipelineStage::ComputeShader;
			barrier.dstStage      = EPipelineStage::ComputeShader;

			cmdList.CmdInsertBarrier(barrier);
		}

		Push push;
		
		push.src         = m_SortBufferA.Get(clock.m_FrameIndex)->GetDeviceAddress();
		push.dst         = m_SortBufferB.Get(clock.m_FrameIndex)->GetDeviceAddress(); 
		push.hist        = m_HistBuffer.Get(clock.m_FrameIndex)->GetDeviceAddress();
		push.numElements = gsCount; 
		push.numWG       = numWG;
		
		RHI::CmdList cmdList;
		
		cmdList.SetComputeCmdList(clock);
		
		MemoryBarrierDesc       barrier{};
		barrier.srcAccess     = EPipelineAccess::ShaderWrite;
		barrier.dstAccess     = EPipelineAccess::ShaderRead;
		barrier.srcStage      = EPipelineStage::ComputeShader;
		barrier.dstStage      = EPipelineStage::ComputeShader;
		
		for (int pass = 0; pass < 4; ++pass) 
		{
			push.shift = 32 + 8 * pass;

			cmdList.CmdBindPipeline(m_HistogramPipeline);

			cmdList.CmdUpdateShaderConstant(&push, sizeof(Push));
			
			cmdList.CmdBindDescriptor(m_HistogramDescriptorList.Get(clock.m_FrameIndex));
			
			cmdList.CmdDispatch(numWG, 1, 1);
			
			cmdList.CmdInsertBarrier(barrier);
			
			cmdList.CmdBindPipeline(m_ScanPipeline);

			cmdList.CmdUpdateShaderConstant(&push, sizeof(Push));
			
			cmdList.CmdBindDescriptor(m_ScanDescriptorList.Get(clock.m_FrameIndex));
			
			cmdList.CmdDispatch(256, 1, 1);
			
			cmdList.CmdInsertBarrier(barrier);

			cmdList.CmdBindPipeline(m_ScatterPipeline);

			cmdList.CmdUpdateShaderConstant(&push, sizeof(Push));

			cmdList.CmdBindDescriptor(m_ScatterDescriptorList.Get(clock.m_FrameIndex));

			cmdList.CmdDispatch(numWG, 1, 1);
			
			cmdList.CmdInsertBarrier(barrier);

			std::swap(push.src, push.dst);
		}
	}

}
