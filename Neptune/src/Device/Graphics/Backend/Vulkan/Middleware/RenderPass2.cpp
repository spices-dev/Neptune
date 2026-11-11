/**
* @file RenderPass2.cpp.
* @brief The RenderPass2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderPass2.h"

#include "Device/Graphics/Backend/Vulkan/Converter.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/SwapChain.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/Vulkan/Unit/CommandBuffer.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Middlewares.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/IImageLayout.h"

namespace Neptune::Vulkan::Middleware {
	
	RenderPass2::RenderPass2(Context& context)
		: ContextAccessor(context)
		, m_ImageLayout(context.Get<IMiddlewares>()->GetContext()->Get<IIImageLayout>())
	{}

	void RenderPass2::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE

		VkAttachmentDescription2                      description{};
		description.sType                           = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
		description.format                          = GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().format.format;
		description.samples                         = VK_SAMPLE_COUNT_1_BIT;
		description.loadOp                          = VK_ATTACHMENT_LOAD_OP_CLEAR;
		description.storeOp                         = VK_ATTACHMENT_STORE_OP_STORE;
		description.stencilLoadOp                   = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		description.stencilStoreOp                  = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		description.initialLayout                   = m_ImageLayout->From(VK_IMAGE_LAYOUT_UNDEFINED);
		description.finalLayout                     = m_ImageLayout->From(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
											        
		VkClearValue                                  clearValue{};
		clearValue.color                            = { 0.0f, 0.0f, 0.0f, 1.0f };

		VkPipelineColorBlendAttachmentState           colorBlend{};
		colorBlend.colorWriteMask                   = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			                                          VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlend.blendEnable                      = VK_FALSE;
		colorBlend.srcColorBlendFactor              = VK_BLEND_FACTOR_ONE;
		colorBlend.dstColorBlendFactor              = VK_BLEND_FACTOR_ZERO;
		colorBlend.colorBlendOp                     = VK_BLEND_OP_ADD;
		colorBlend.srcAlphaBlendFactor              = VK_BLEND_FACTOR_ONE;
		colorBlend.dstAlphaBlendFactor              = VK_BLEND_FACTOR_ZERO;
		colorBlend.alphaBlendOp                     = VK_BLEND_OP_ADD;
											        
		VkAttachmentReference2                        attachmentRef{};
		attachmentRef.sType                         = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
		attachmentRef.attachment                    = 0;
		attachmentRef.layout                        = m_ImageLayout->From(VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL);

		m_AttachmentDescriptions.emplace_back(description);
		m_ColorAttachmentReference.emplace_back(attachmentRef);
		m_ColorBlends.emplace_back(colorBlend);
		m_ClearValues.emplace_back(clearValue);

		StoreExtent(GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().surfaceSize);
	}

	void RenderPass2::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		VkAttachmentDescription2                      description{};
		description.sType                           = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
		description.format                          = ToVkFormat(renderTarget->GetFormat());
		description.samples                         = VK_SAMPLE_COUNT_1_BIT;
		description.loadOp                          = ToVkAttachmentLoadOp(info.loadOp);
		description.storeOp                         = VK_ATTACHMENT_STORE_OP_STORE;
		description.stencilLoadOp                   = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		description.stencilStoreOp                  = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		description.initialLayout                   = m_ImageLayout->From(ToVkImageLayout(info.inLayout));
		description.finalLayout                     = m_ImageLayout->From(ToVkImageLayout(info.outLayout));
		
		if (info.loadOp == AttachmentOP::Clear)
		{
			VkClearValue                              clearValue{};
			clearValue.color                        = { 0.0f, 0.0f, 0.0f, 1.0f };

			m_ClearValues.emplace_back(clearValue);
		}

		VkPipelineColorBlendAttachmentState           colorBlend{};
		colorBlend.colorWriteMask                   = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			                                          VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

		if (!info.enableBlend)
		{
			colorBlend.blendEnable                  = VK_FALSE;
			colorBlend.srcColorBlendFactor          = VK_BLEND_FACTOR_ONE;
			colorBlend.dstColorBlendFactor          = VK_BLEND_FACTOR_ZERO;
			colorBlend.colorBlendOp                 = VK_BLEND_OP_ADD;
			colorBlend.srcAlphaBlendFactor          = VK_BLEND_FACTOR_ONE;
			colorBlend.dstAlphaBlendFactor          = VK_BLEND_FACTOR_ZERO;
			colorBlend.alphaBlendOp                 = VK_BLEND_OP_ADD;
		}									       
		else								       
		{									       
			colorBlend.blendEnable                  = VK_TRUE;
			colorBlend.srcColorBlendFactor          = VK_BLEND_FACTOR_SRC_ALPHA;
			colorBlend.dstColorBlendFactor          = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlend.colorBlendOp                 = VK_BLEND_OP_ADD;
			colorBlend.srcAlphaBlendFactor          = VK_BLEND_FACTOR_ONE;
			colorBlend.dstAlphaBlendFactor          = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlend.alphaBlendOp                 = VK_BLEND_OP_ADD;
		}

		VkAttachmentReference2                        attachmentRef{};
		attachmentRef.sType                         = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
		attachmentRef.attachment                    = static_cast<uint32_t>(m_ColorAttachmentReference.size());
		attachmentRef.layout                        = m_ImageLayout->From(VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL);

		m_AttachmentDescriptions.emplace_back(description);
		m_ColorAttachmentReference.emplace_back(attachmentRef);
		m_ColorBlends.emplace_back(colorBlend);
		m_ImageViews.emplace_back(renderTarget->GetRHIImpl<RenderTarget>()->GetView());

		StoreExtent({ renderTarget->GetWidth(), renderTarget->GetHeight() });
	}

	void RenderPass2::Build(uint32_t count)
	{
		NEPTUNE_PROFILE_ZONE

		{
			VkSubpassDescription2                         description{};
			description.sType                           = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
			description.pipelineBindPoint               = VK_PIPELINE_BIND_POINT_GRAPHICS;
			description.colorAttachmentCount            = static_cast<uint32_t>(m_ColorAttachmentReference.size());
			description.pColorAttachments               = m_ColorAttachmentReference.data();
			description.pDepthStencilAttachment         = nullptr;
			description.inputAttachmentCount            = 0;
			description.pInputAttachments               = nullptr;

			VkSubpassDependency2                          dependency{};
			dependency.sType                            = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
			dependency.srcSubpass                       = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass                       = 0;
			dependency.srcStageMask                     = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.dstStageMask                     = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.srcAccessMask                    = 0;
			dependency.dstAccessMask                    = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			dependency.dependencyFlags                  = 0;

			VkRenderPassCreateInfo2		                  info{};
			info.sType                                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
			info.attachmentCount                        = static_cast<uint32_t>(m_AttachmentDescriptions.size());
			info.pAttachments                           = m_AttachmentDescriptions.data();
			info.subpassCount                           = 1;
			info.pSubpasses                             = &description;
			info.dependencyCount                        = 1;
			info.pDependencies                          = &dependency;
		
			m_RenderPass.CreateRenderPass2(GetContext().Get<IDevice>()->Handle(), info);

			DEBUGUTILS_SETOBJECTNAME(m_RenderPass, "RenderPass")
		}

		const bool swapChainInUsed = m_ImageViews.size() < m_AttachmentDescriptions.size();

		for (uint32_t i = 0; i < count; i++)
		{
			auto imageViews = m_ImageViews;

			if (swapChainInUsed)
			{
				imageViews.insert(imageViews.begin(), GetContext().Get<ISwapChain>()->GetView(i));
			}

			VkFramebufferCreateInfo						  info{};
			info.sType						            = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			info.renderPass					            = m_RenderPass.GetHandle();
			info.attachmentCount			            = static_cast<uint32_t>(imageViews.size());
			info.pAttachments				            = imageViews.data();
			info.width                                  = m_Extent.value().width;
			info.height                                 = m_Extent.value().height;
			info.layers                                 = 1;

			auto frameBuffer = CreateSP<Unit::FrameBuffer>();

			frameBuffer->CreateFrameBuffer(GetContext().Get<IDevice>()->Handle(), info);

			m_FrameBuffers.emplace_back(frameBuffer);

			DEBUGUTILS_SETOBJECTNAME(*frameBuffer, "FrameBuffer")
		}
	}

	void RenderPass2::BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex)
	{
		NEPTUNE_PROFILE_ZONE
		
		VkRenderPassBeginInfo                         info{};
		info.sType                                  = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		info.renderPass                             = Handle();
		info.framebuffer                            = m_FrameBuffers[frameBufferIndex]->GetHandle();
		info.renderArea.offset                      = { 0, 0 };
		info.renderArea.extent                      = m_Extent.value();
		info.clearValueCount                        = static_cast<uint32_t>(m_ClearValues.size());
		info.pClearValues                           = m_ClearValues.data();

		commandBuffer->BeginRenderPass(info, VK_SUBPASS_CONTENTS_INLINE);
	}
	
	void RenderPass2::EndRenderPass(const Unit::CommandBuffer* commandBuffer) const
	{
		NEPTUNE_PROFILE_ZONE
		
		commandBuffer->EndRenderPass();
	}

	const VkPipelineColorBlendStateCreateInfo& RenderPass2::GetColorBlendInfo()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_ColorBlendInfo.sType            = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		m_ColorBlendInfo.attachmentCount  = static_cast<uint32_t>(m_ColorBlends.size());
		m_ColorBlendInfo.pAttachments     = m_ColorBlends.data();
		
		return m_ColorBlendInfo;
	}
	
	void RenderPass2::StoreExtent(const VkExtent2D& extent)
	{
		NEPTUNE_PROFILE_ZONE

		if (m_Extent.has_value()) return;

		m_Extent = extent;
	}
	
}

#endif