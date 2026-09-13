/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/SwapChain.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DynamicRendering.h"
#include "Device/Graphics/Backend/Vulkan/Extension/UnifiedImageLayouts.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"

namespace Neptune::Vulkan {

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE

		VkAttachmentDescription                       description{};
		description.format                          = GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().format.format;
		description.samples                         = VK_SAMPLE_COUNT_1_BIT;
		description.loadOp                          = VK_ATTACHMENT_LOAD_OP_CLEAR;
		description.storeOp                         = VK_ATTACHMENT_STORE_OP_STORE;
		description.stencilLoadOp                   = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		description.stencilStoreOp                  = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		description.initialLayout                   = VK_IMAGE_LAYOUT_UNDEFINED;
		description.finalLayout                     = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
											        
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
											        
		VkAttachmentReference                         attachmentRef{};
		attachmentRef.attachment                    = 0;
		attachmentRef.layout                        = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		m_AttachmentDescriptions.emplace_back(description);
		m_ColorAttachmentReference.emplace_back(attachmentRef);
		m_ColorAttachmentFormats.emplace_back(description.format);
		m_ColorBlends.emplace_back(colorBlend);
		m_ClearValues.emplace_back(clearValue);

		StoreExtent(GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().surfaceSize);
	}

	void RenderPass::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		VkAttachmentDescription                       description{};
		description.format                          = ToVkFormat(renderTarget->GetFormat());
		description.samples                         = VK_SAMPLE_COUNT_1_BIT;
		description.loadOp                          = ToVkAttachmentLoadOp(info.loadOp);
		description.storeOp                         = VK_ATTACHMENT_STORE_OP_STORE;
		description.stencilLoadOp                   = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		description.stencilStoreOp                  = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		description.initialLayout                   = ToVkImageLayout(info.inLayout);
		description.finalLayout                     = ToVkImageLayout(info.outLayout);
		
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

		VkAttachmentReference                         attachmentRef{};
		attachmentRef.attachment                    = static_cast<uint32_t>(m_ColorAttachmentReference.size());
		attachmentRef.layout                        = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		m_AttachmentDescriptions.emplace_back(description);
		m_ColorAttachmentReference.emplace_back(attachmentRef);
		m_ColorAttachmentFormats.emplace_back(description.format);
		m_ColorBlends.emplace_back(colorBlend);
		m_ImageViews.emplace_back(renderTarget->GetRHIImpl<RenderTarget>()->GetView());

		StoreExtent({ renderTarget->GetWidth(), renderTarget->GetHeight() });
	}

	void RenderPass::Build(uint32_t count)
	{
		NEPTUNE_PROFILE_ZONE

		{
			VkSubpassDescription                          description{};
			description.pipelineBindPoint               = VK_PIPELINE_BIND_POINT_GRAPHICS;
			description.colorAttachmentCount            = static_cast<uint32_t>(m_ColorAttachmentReference.size());
			description.pColorAttachments               = m_ColorAttachmentReference.data();
			description.pDepthStencilAttachment         = nullptr;
			description.inputAttachmentCount            = 0;
			description.pInputAttachments               = nullptr;

			VkSubpassDependency                           dependency{};
			dependency.srcSubpass                       = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass                       = 0;
			dependency.srcStageMask                     = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.dstStageMask                     = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.srcAccessMask                    = 0;
			dependency.dstAccessMask                    = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			dependency.dependencyFlags                  = 0;

			VkRenderPassCreateInfo		                  info{};
			info.sType                                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			info.attachmentCount                        = static_cast<uint32_t>(m_AttachmentDescriptions.size());
			info.pAttachments                           = m_AttachmentDescriptions.data();
			info.subpassCount                           = 1;
			info.pSubpasses                             = &description;
			info.dependencyCount                        = 1;
			info.pDependencies                          = &dependency;
		
			m_RenderPass.CreateRenderPass(GetContext().Get<IDevice>()->Handle(), info);

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

	void RenderPass::BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex) const
	{
		NEPTUNE_PROFILE_ZONE

		if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IDynamicRendering>())
		{
			std::vector<VkRenderingAttachmentInfo>    attachmentInfos{};
			
			if (m_ImageViews.size() < m_AttachmentDescriptions.size())
			{
				VkRenderingAttachmentInfo                 colorAttachment{};
				colorAttachment.sType                   = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
				colorAttachment.imageView               = GetContext().Get<ISwapChain>()->GetView(frameBufferIndex);
				colorAttachment.imageLayout             = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL;
				colorAttachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_LOAD;
				colorAttachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
				colorAttachment.clearValue              = {};
				
				if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IUnifiedImageLayouts>())
				{
					colorAttachment.imageLayout         = VK_IMAGE_LAYOUT_GENERAL;
				}
				
				attachmentInfos.emplace_back(colorAttachment);
			}
			
			for (int i = 0; i < m_ImageViews.size(); i++)
			{
				VkRenderingAttachmentInfo                 colorAttachment{};
				colorAttachment.sType                   = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
				colorAttachment.imageView               = m_ImageViews[i];
				colorAttachment.imageLayout             = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL;
				colorAttachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_LOAD;
				colorAttachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
				colorAttachment.clearValue              = {};
				
				if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IUnifiedImageLayouts>())
				{
					colorAttachment.imageLayout         = VK_IMAGE_LAYOUT_GENERAL;
				}
				
				attachmentInfos.emplace_back(colorAttachment);
			}
			
			VkRenderingInfo                           info{};
			info.sType                              = VK_STRUCTURE_TYPE_RENDERING_INFO;
			info.renderArea                      = {  { 0, 0 }, *m_Extent };
			info.layerCount                         = 1;
			info.colorAttachmentCount               = attachmentInfos.size();
			info.pColorAttachments                  = attachmentInfos.data();
			
			commandBuffer->BeginRendering(info);
		}
		else
		{
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
	}

	void RenderPass::StoreExtent(const VkExtent2D& extent)
	{
		NEPTUNE_PROFILE_ZONE

		if (m_Extent.has_value()) return;

		m_Extent = extent;
	}
	
}

#endif