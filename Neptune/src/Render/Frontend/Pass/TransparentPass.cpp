/**
* @file TransparentPass.cpp.
* @brief The TransparentPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "TransparentPass.h"
#include "Device/Graphics/Frontend/RHI/Pipeline.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"
#include "Device/Graphics/Frontend/RHI/DescriptorList.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"
#include "Device/Graphics/Frontend/RHI/IndexBuffer.h"
#include "Device/Graphics/Frontend/RHI/Buffer.h"
#include "Resource/Shader/Shader.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/ResourcePool/ResourcePool.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"
#include "World/Component/SOPComponent.h"
#include "Asset/SOP/GS3D.h"
#include "Resource/Buffer/Buffer.h"

namespace Neptune::Render {

	void TransparentPass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE
		
		{
			auto& resourcePool = ResourcePool<Buffer>::Instance();

			for (int i = 0; i < MaxFrameInFlight; ++i)
			{
				std::stringstream ss;
				ss << "TransparentSortBuffer_" << i;
				
				auto s = resourcePool.Access(ss.str());
			
				m_SortBuffer.Get(i) = s->GetRHIResource();
			}
		}
		
		RenderTargetAttachmentInfo   info{};
		info.loadOp                = AttachmentOP::Load;
		info.enableBlend           = true;
		info.inLayout              = AttachmentLayout::ColorAttachment;
		info.outLayout             = AttachmentLayout::ColorAttachment;

		m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddColorAttachment(ResourcePool<RenderTarget>::Instance().Access("Scene")->GetRHIResource(), info);
		m_RenderPass->Build();
		
		for (int i = 0; i < MaxFrameInFlight; ++i)
		{
			m_DescriptorList.Get(i) = CreateSP<RHI::DescriptorList>();
			m_DescriptorList.Get(i)->AddShaderConstant(sizeof(uint32_t));
			m_DescriptorList.Get(i)->AddUniformBuffer(1, 0, sizeof(uint64_t));
			m_DescriptorList.Get(i)->AddUniformBuffer(1, 1, sizeof(uint64_t));
			m_DescriptorList.Get(i)->CombineSharedLayout();
			m_DescriptorList.Get(i)->Build();
		}

		m_Pipeline = CreateSP<RHI::Pipeline>();
		m_Pipeline->SetDefault();
		m_Pipeline->SetRenderPass(m_RenderPass);
		m_Pipeline->SetDescriptorList(m_DescriptorList.Get(0));
		m_Pipeline->SetCullMode(ECullMode::None);
		m_Pipeline->SetTopology(ETopology::TriangleStrip);
		
		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("TransparentPassVert"))
			{
				auto s = resourcePool.Load<Shader>("TransparentPassVert");

				s->SetStage(ShaderStage::Vertex);
				s->SetSource("Shaders/src/TransparentPass.vert.spv");
			}

            auto shader = resourcePool.Access("TransparentPassVert");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("TransparentPassFrag"))
			{
				auto s = resourcePool.Load<Shader>("TransparentPassFrag");

				s->SetStage(ShaderStage::Fragment);
				s->SetSource("Shaders/src/TransparentPass.frag.spv");
			}

            auto shader = resourcePool.Access("TransparentPassFrag");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		m_Pipeline->BuildGraphicPipeline();
		
		
		{
			static constexpr uint32_t indices[] = { 0, 1, 2, 3 };
			
			m_IndexBuffer = CreateSP<RHI::IndexBuffer>();
		
			m_IndexBuffer->CreateBuffer(16);
		
			m_IndexBuffer->WriteToBuffer(indices, 16);
		
			m_IndexBuffer->Flush(16);
		}
	}

	void TransparentPass::OnCollectRHI(Scene* scene)
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
		
		auto gsCount = item->GetPointCount();
		
		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();
		
		auto sortBufferAddress = m_SortBuffer.Get(clock.m_FrameIndex)->GetDeviceAddress();
		
		m_DescriptorList.Get(clock.m_FrameIndex)->UpdateUniformBuffer(1, 0, &item->GetDescDeviceAddress());
		
		m_DescriptorList.Get(clock.m_FrameIndex)->UpdateUniformBuffer(1, 1, &sortBufferAddress);

		RHI::CmdList cmdList;

		cmdList.SetGraphicCmdList(clock);

		cmdList.SetRenderPass(m_RenderPass);

		cmdList.CmdBeginRenderPass();

		cmdList.CmdBindPipeline(m_Pipeline);

		cmdList.CmdBindDescriptor(m_DescriptorList.Get(clock.m_FrameIndex));

		cmdList.CmdBindIndexBuffer(m_IndexBuffer);
		
		cmdList.CmdUpdateShaderConstant(&gsCount, sizeof(gsCount));
		
		cmdList.CmdDrawInstance(4, gsCount, 0, 0, 0);

		cmdList.CmdEndRenderPass();
	}

}
