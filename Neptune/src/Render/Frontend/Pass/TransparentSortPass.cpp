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

	namespace {
		
		constexpr uint32_t kMaxTransparent = 18000000;
		
		struct UBO {
			uint64_t sortAddress;
		};
		
		struct SortParam
		{
			uint32_t stage       = 0;
			uint32_t passOfStage = 0;
			uint32_t numElements = 0;
		};
		
		SP<std::array<SortParam, 30000>> sortParams{};
		
		uint32_t NextPowerOfTwo(uint32_t n)
		{
			if (n == 0) return 1;

			n -= 1;
			n |= n >> 1;
			n |= n >> 2;
			n |= n >> 4;
			n |= n >> 8;
			n |= n >> 16;
			return n + 1;
		}
		
		decltype(sortParams) BuildBitonicSortParams(uint32_t paddedN)
		{
			decltype(sortParams) allParams = CreateSP<std::array<SortParam, 30000>>();
			
			uint32_t numStages = 0;
			for (uint32_t v = paddedN; v > 1; v >>= 1)
			{
				++numStages;
			}

			uint32_t iter = 0;
			
			for (uint32_t stage = 0; stage < numStages; ++stage)
			{
				for (uint32_t passOfStage = 0; passOfStage <= stage; ++passOfStage)
				{
					(*allParams)[iter++] = SortParam{ stage, passOfStage, paddedN };
				}
			}

			return allParams;
		}
	}
	
	void TransparentSortPass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE

		{
			auto& resourcePool = ResourcePool<Buffer>::Instance();

			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				std::stringstream ss;
				ss << "TransparentSortBuffer_" << i;
				
				if (!resourcePool.Has(ss.str()))
				{
					auto s = resourcePool.Load<Buffer>(ss.str(), BufferCreateInfo{ kMaxTransparent * sizeof(uint64_t) } );
				
					s->GetRHIResource()->SetName(ss.str());
				}
				
				m_SortBuffer.Get(i) = resourcePool.Access(ss.str())->GetRHIResource();
			}
		}
		
		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_KDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_KDescriptorList.Get(i)->AddShaderConstant(2 * sizeof(uint32_t));
				m_KDescriptorList.Get(i)->AddUniformBuffer(1, 0, sizeof(uint64_t));
				m_KDescriptorList.Get(i)->AddUniformBuffer(1, 1, sizeof(uint64_t));
				m_KDescriptorList.Get(i)->CombineSharedLayout();
				m_KDescriptorList.Get(i)->Build();
			}
			
			m_KPipeline = CreateSP<RHI::Pipeline>();
			m_KPipeline->SetDefault();
			m_KPipeline->SetDescriptorList(m_KDescriptorList.Get(0));
			
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("TransparentSortPassKeyGenComp"))
			{
				auto s = resourcePool.Load<Shader>("TransparentSortPassKeyGenComp");

				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TransparentSortPassKeyGenComp.comp.spv");
			}

			auto shader = resourcePool.Access("TransparentSortPassKeyGenComp");

			m_KPipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
			
			m_KPipeline->BuildComputePipeline();
		}

		{
			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				m_SDescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
				m_SDescriptorList.Get(i)->AddShaderConstant(sizeof(uint32_t));
				m_SDescriptorList.Get(i)->AddUniformBuffer(1, 0, sizeof(uint64_t));
				m_SDescriptorList.Get(i)->AddUniformBuffer(1, 1, sizeof(uint64_t));
				m_SDescriptorList.Get(i)->CombineSharedLayout();
				m_SDescriptorList.Get(i)->Build();
			}
			
			m_SPipeline = CreateSP<RHI::Pipeline>();
			m_SPipeline->SetDefault();
			m_SPipeline->SetDescriptorList(m_SDescriptorList.Get(0));
			
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("TransparentSortPassComp"))
			{
				auto s = resourcePool.Load<Shader>("TransparentSortPassComp");

				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TransparentSortPass.comp.spv");
			}

            auto shader = resourcePool.Access("TransparentSortPassComp");

			m_SPipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
			
			m_SPipeline->BuildComputePipeline();
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

		uint32_t gsCount = item->GetPointCount();
		
		uint32_t paddedN = NextPowerOfTwo(gsCount);
		
		{
			if (!m_SortParam)
			{
				sortParams = BuildBitonicSortParams(paddedN);
				
				m_SortParam = CreateSP<RHI::Buffer>();
				
				m_SortParam->CreateBuffer(sizeof(*sortParams));
				
				m_SortParam->WriteToBuffer(sortParams->data(), sizeof(*sortParams));
				
				m_SortParam->Flush(sizeof(*sortParams));
			}
		}
		
		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();
		
		{
			auto sortBufferAddress = m_SortBuffer.Get(clock.m_FrameIndex)->GetDeviceAddress();
		
			m_KDescriptorList.Get(clock.m_FrameIndex)->UpdateUniformBuffer(1, 0, &item->GetDescDeviceAddress());
			
			m_KDescriptorList.Get(clock.m_FrameIndex)->UpdateUniformBuffer(1, 1, &sortBufferAddress);
			
			RHI::CmdList cmdList;

			cmdList.SetComputeCmdList(clock);

			cmdList.CmdBindPipeline(m_KPipeline);

			cmdList.CmdBindDescriptor(m_KDescriptorList.Get(clock.m_FrameIndex));
			
			cmdList.CmdUpdateShaderConstant(&paddedN, sizeof(uint32_t));
			
			cmdList.CmdUpdateShaderConstant(&gsCount, sizeof(uint32_t), sizeof(uint32_t));
			
			cmdList.CmdDispatch((paddedN + 255) / 256, 1, 1);
			
			MemoryBarrierdDesc      barrier{};
			barrier.srcAccess     = EPipelineAccess::ShaderWrite;
			barrier.dstAccess     = EPipelineAccess::ShaderRead;
			barrier.srcStage      = EPipelineStage::ComputeShader;
			barrier.dstStage      = EPipelineStage::ComputeShader;

			cmdList.CmdInsertBarrier(barrier);
		}
		
		{
			auto sortBufferAddress = m_SortBuffer.Get(clock.m_FrameIndex)->GetDeviceAddress();
		
			m_SDescriptorList.Get(clock.m_FrameIndex)->UpdateUniformBuffer(1, 0, &sortBufferAddress);
		
			auto sortParamAddress = m_SortParam->GetDeviceAddress();
			
			m_SDescriptorList.Get(clock.m_FrameIndex)->UpdateUniformBuffer(1, 1, &sortParamAddress);
		
			RHI::CmdList cmdList;

			cmdList.SetComputeCmdList(clock);

			cmdList.CmdBindPipeline(m_SPipeline);

			cmdList.CmdBindDescriptor(m_SDescriptorList.Get(clock.m_FrameIndex));
		
			uint32_t iter = 0;
		
			uint32_t numStages = 0;
			for (uint32_t v = paddedN; v > 1; v >>= 1)
			{
				++numStages;
			}

			for (uint32_t stage = 0; stage < numStages; ++stage)
			{
				for (uint32_t passOfStage = 0; passOfStage <= stage; ++passOfStage)
				{
					cmdList.CmdUpdateShaderConstant(&iter, sizeof(iter));
				
					uint32_t groupCount = (paddedN / 2 + 255) / 256;
					
					cmdList.CmdDispatch(groupCount, 1, 1);
				
					MemoryBarrierdDesc          barrier{};
					barrier.srcAccess         = EPipelineAccess::ShaderWrite;
					barrier.dstAccess         = EPipelineAccess::ShaderRead;
					barrier.srcStage          = EPipelineStage::ComputeShader;
					barrier.dstStage          = EPipelineStage::ComputeShader;
				
					cmdList.CmdInsertBarrier(barrier);
				
					++iter;
				}
			}
		}
	}

}