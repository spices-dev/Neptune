/**
* @file BasePass.cpp.
* @brief The BasePass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "BasePass.h"
#include "Device/Graphics/Frontend/RHI/Pipeline.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"
#include "Device/Graphics/Frontend/RHI/DescriptorList.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"
#include "Device/Graphics/Frontend/RHI/RenderTarget.h"
#include "Resource/Shader/Shader.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/ResourcePool/ResourcePool.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"

namespace Neptune::Render {

	void BasePass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE
		
		auto& resourcePool = ResourcePool<RenderTarget>::Instance();
		
		{
			RenderTargetCreateInfo    info{};
			info.format             = TextureFormat::RGBA16_SFLOAT;
			info.domain             = TextureDomain::Texture2D;
			info.width              = m_RTSize.x;
			info.height             = m_RTSize.y;
			info.usage.Set(Graphic::EImageUsage::ColorAttachment);
			info.usage.Set(Graphic::EImageUsage::Sampler);
			info.usage.Set(Graphic::EImageUsage::TransferDst);

			auto scene = CreateSP<RenderTarget>(info);

			resourcePool.Registry("Scene", scene);
			
			scene->SetName("Scene");
		}
		
		{
			RenderTargetCreateInfo    info{};
			info.usage.Set(Graphic::EImageUsage::Sampler);
			info.usage.Set(Graphic::EImageUsage::TransferDst);

			if (!resourcePool.Has("CurrDecodeRT"))
			{
				resourcePool.Load<RenderTarget>("CurrDecodeRT", info);
			}
		}

		RenderTargetAttachmentInfo                  info{};
		info.loadOp                               = AttachmentOP::Clear;
		info.enableBlend                          = false;
		info.inLayout                             = Graphic::EImageLayout::Undefined;
		info.outLayout                            = Graphic::EImageLayout::Attachment;

		m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddColorAttachment(ResourcePool<RenderTarget>::Instance().Access("Scene")->GetRHIResource(), info);
		m_RenderPass->Build();
		
		m_DescriptorList = CreateSP<RHI::DescriptorList>();
		m_DescriptorList->AddUniformTexture(1, 0, ResourcePool<RenderTarget>::Instance().Access("CurrDecodeRT")->GetRHIResource());
		m_DescriptorList->CombineSharedLayout();
		m_DescriptorList->Build();

		m_Pipeline = CreateSP<RHI::Pipeline>();
		m_Pipeline->SetDefault();
		m_Pipeline->SetRenderPass(m_RenderPass);
		m_Pipeline->SetDescriptorList(m_DescriptorList);
		m_Pipeline->SetCullMode(ECullMode::None);
		
		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("BasePassVert"))
			{
				auto s = resourcePool.Load<Shader>("BasePassVert");

				s->SetStage(ShaderStage::Vertex);
				s->SetSource("Shaders/src/BasePass.vert.slang.spv");
			}

            auto shader = resourcePool.Access("BasePassVert");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.Has("BasePassFrag"))
			{
				auto s = resourcePool.Load<Shader>("BasePassFrag");

				s->SetStage(ShaderStage::Fragment);
				s->SetSource("Shaders/src/BasePass.frag.slang.spv");
			}

            auto shader = resourcePool.Access("BasePassFrag");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		m_Pipeline->BuildGraphicPipeline();
	}

	void BasePass::OnCollectRHI(Scene* scene)
	{
		NEPTUNE_PROFILE_ZONE
		
		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

		m_DescriptorList->UpdateUniformTexture(1, 0, ResourcePool<RenderTarget>::Instance().Access("GS3DScene_" + clock.m_FrameIndex)->GetRHIResource());

		RHI::CmdList cmdList;

		cmdList.SetGraphicCmdList(clock);

		cmdList.SetRenderPass(m_RenderPass);

		cmdList.CmdBeginRenderPass();

		cmdList.CmdSetViewport(m_RTSize);

		cmdList.CmdBindPipeline(m_Pipeline);

		cmdList.CmdBindDescriptor(m_DescriptorList);

		cmdList.CmdDraw(3, 1, 0, 0);

		cmdList.CmdEndRenderPass();
	}

}