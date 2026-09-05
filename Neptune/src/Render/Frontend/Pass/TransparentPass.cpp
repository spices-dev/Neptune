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
#include "Resource/Shader/Shader.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/ResourcePool/ResourcePool.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"
#include "World/Component/SOPComponent.h"
#include "Asset/SOP/GS3D.h"

namespace Neptune::Render {

	void TransparentPass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE
		
		RenderTargetAttachmentInfo   info{};
		info.loadOp                = AttachmentOP::Load;
		info.enableBlend           = true;
		info.inLayout              = AttachmentLayout::ColorAttachment;
		info.outLayout             = AttachmentLayout::ColorAttachment;

		m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddColorAttachment(ResourcePool<RenderTarget>::Instance().Access("Scene")->GetRHIResource(), info);
		m_RenderPass->Build();
		
		m_DescriptorList = CreateSP<RHI::DescriptorList>();
		m_DescriptorList->CombineSharedLayout();
		m_DescriptorList->Build();

		m_Pipeline = CreateSP<RHI::Pipeline>();
		m_Pipeline->SetDefault();
		m_Pipeline->SetRenderPass(m_RenderPass);
		m_Pipeline->SetDescriptorList(m_DescriptorList);
		m_Pipeline->SetCullMode(CullMode::None);
		
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
		
		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

		RHI::CmdList cmdList;

		cmdList.SetGraphicCmdList(clock);

		cmdList.SetRenderPass(m_RenderPass);

		cmdList.CmdBeginRenderPass();

		cmdList.CmdBindPipeline(m_Pipeline);

		cmdList.CmdBindDescriptor(m_DescriptorList);

		cmdList.CmdBindIndexBuffer(m_IndexBuffer);
		
		cmdList.CmdDrawInstance(4, item->GetPointCount(), 0, 0, 0);

		cmdList.CmdEndRenderPass();
	}

}