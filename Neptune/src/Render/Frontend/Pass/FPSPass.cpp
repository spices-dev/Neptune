/**
* @file FPSPass.cpp.
* @brief The FPSPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "FPSPass.h"
#include "Device/Graphics/Frontend/RHI/Pipeline.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"
#include "Device/Graphics/Frontend/RHI/DescriptorList.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"
#include "Resource/Shader/Shader.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/ResourcePool/ResourcePool.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"

namespace Neptune::Render {

	void FPSPass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE
		
		RenderTargetAttachmentInfo   info{};
		info.loadOp                = AttachmentOP::Load;
		info.enableBlend           = true;
		info.inLayout              = Graphic::EImageLayout::Attachment;
		info.outLayout             = Graphic::EImageLayout::ShaderRead;

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
		m_Pipeline->SetCullMode(ECullMode::None);
		
		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("FPSPassVert"))
			{
				auto s = resourcePool.Load<Shader>("FPSPassVert");

				s->SetStage(ShaderStage::Vertex);
				s->SetSource("Shaders/spv/FPSPass.vert.slang.spv");
			}

            auto shader = resourcePool.Access("FPSPassVert");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("FPSPassFrag"))
			{
				auto s = resourcePool.Load<Shader>("FPSPassFrag");

				s->SetStage(ShaderStage::Fragment);
				s->SetSource("Shaders/spv/FPSPass.frag.slang.spv");
			}

            auto shader = resourcePool.Access("FPSPassFrag");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		m_Pipeline->BuildGraphicPipeline();
	}

	void FPSPass::OnCollectRHI(Scene* scene)
	{
		NEPTUNE_PROFILE_ZONE

		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

		RHI::CmdList cmdList;

		cmdList.SetGraphicCmdList(clock);

		cmdList.SetRenderPass(m_RenderPass);

		cmdList.CmdBeginRenderPass();

		cmdList.CmdBindPipeline(m_Pipeline);

		cmdList.CmdBindDescriptor(m_DescriptorList);

		cmdList.CmdDraw(3, 1, 0, 0);

		cmdList.CmdEndRenderPass();
	}

}