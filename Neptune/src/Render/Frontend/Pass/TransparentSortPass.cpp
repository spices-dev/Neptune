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
		
		constexpr uint32_t kMaxTransparent = 1000000;
		
		struct UBO {
			uint64_t sortAddress;
		};
		
		struct SortParam
		{
			uint32_t stage       = 0;
			uint32_t passOfStage = 0;
			uint32_t numElements = 0;
		};
		
		std::array<SortParam, 50> sortParams{};
		
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
		
		std::array<SortParam, 50> BuildBitonicSortParams(uint32_t paddedN)
		{
			std::array<SortParam, 50> allParams;
			
			uint32_t numStages = 0;
			for (uint32_t v = paddedN; v > 1; v >>= 1)
			{
				++numStages;
			}

			uint32_t iter = 0;
			
			for (uint32_t stage = 1; stage <= numStages; ++stage)
			{
				for (uint32_t passOfStage = 0; passOfStage < stage; ++passOfStage)
				{
					allParams[iter++] = SortParam{ stage, passOfStage, paddedN };
				}
			}

			return allParams;
		}
	}
	
	void TransparentSortPass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE

		m_DescriptorList = CreateSP<RHI::DescriptorList>();
		m_DescriptorList->AddDynamicUniformBuffer(1, 0, sizeof(sortParams));
		m_DescriptorList->AddUniformBuffer(2, 0, sizeof(uint64_t));
		m_DescriptorList->CombineSharedLayout();
		m_DescriptorList->Build();

		m_Pipeline = CreateSP<RHI::Pipeline>();
		m_Pipeline->SetDefault();
		m_Pipeline->SetDescriptorList(m_DescriptorList);
		
		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("TransparentSortPassComp"))
			{
				auto s = resourcePool.Load<Shader>("TransparentSortPassComp");

				s->SetStage(ShaderStage::Compute);
				s->SetSource("Shaders/src/TransparentSortPass.comp.spv");
			}

            auto shader = resourcePool.Access("TransparentSortPassComp");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		m_Pipeline->BuildComputePipeline();
		
		{
			auto& resourcePool = ResourcePool<Buffer>::Instance();

			if (!resourcePool.Has("TransparentSortBuffer"))
			{
				auto s = resourcePool.Load<Buffer>("TransparentSortBuffer", BufferCreateInfo{ kMaxTransparent * sizeof(uint32_t) } );
			}

			auto shader = resourcePool.Access("TransparentSortBuffer");
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

		uint32_t paddedN = NextPowerOfTwo(item->GetPointCount());
		
		sortParams = BuildBitonicSortParams(paddedN);
		
		auto sortBufferAddress = ResourcePool<Buffer>::Instance().Access("TransparentSortBuffer")->GetRHIResource()->GetDeviceAddress();
		
		m_DescriptorList->UpdateUniformBuffer(1, 0, sortParams.data());
		
		m_DescriptorList->UpdateUniformBuffer(2, 0, &sortBufferAddress);
		
		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();
		
		RHI::CmdList cmdList;

		cmdList.SetComputeCmdList(clock);

		cmdList.CmdBindPipeline(m_Pipeline);

		cmdList.CmdBindDescriptor(m_DescriptorList);
		
		uint32_t iter = 0;
		
		uint32_t numStages = (uint32_t)std::log2(paddedN);

		for (uint32_t stage = 1; stage <= numStages; ++stage)
		{
			for (uint32_t passOfStage = 0; passOfStage < stage; ++passOfStage)
			{
				m_DescriptorList->UpdateDynamicUniformBufferOffset(1, sizeof(SortParam) * iter++);
				
				cmdList.CmdBindDescriptor(m_DescriptorList);
				
				uint32_t groupCount = (paddedN / 2 + 255) / 256;
				cmdList.CmdDispatch(groupCount, 1, 1);
				
				MemoryBarrier          barrier{};
				barrier.srcAccess    = EPipelineAccess::ShaderWrite;
				barrier.dstAccess    = EPipelineAccess::ShaderRead;
				barrier.srcStage     = EPipelineStage::ComputeShader;
				barrier.dstStage     = EPipelineStage::ComputeShader;
				
				cmdList.CmdInsertBarrier(barrier);
			}
		}
	}

}