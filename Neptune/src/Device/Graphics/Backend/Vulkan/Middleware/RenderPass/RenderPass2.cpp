/**
* @file RenderPass2.cpp.
* @brief The RenderPass2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderPass2.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"
#include "Device/Graphics/Backend/Vulkan/Extension/UnifiedImageLayouts.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/SwapChain.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/Vulkan/Unit/CommandBuffer.h"

namespace Neptune::Vulkan::Middleware {

	void RenderPass2::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE
		
		VkClearValue                                  clearValue{};
		clearValue.color                            = { 0.0f, 0.0f, 0.0f, 1.0f };
		
		VkRenderingAttachmentInfo                     attachmentInfo{};
		attachmentInfo.sType                        = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
		attachmentInfo.imageView                    = VK_NULL_HANDLE;
		attachmentInfo.imageLayout                  = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL;
		attachmentInfo.loadOp                       = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachmentInfo.storeOp                      = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentInfo.clearValue                   = clearValue;
		
		if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IUnifiedImageLayouts>())
		{
			attachmentInfo.imageLayout              = VK_IMAGE_LAYOUT_GENERAL;
		}
		
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
		
		m_SwapChainImageIndex = m_AttachmentInfos.size();
		m_ColorAttachmentFormats.emplace_back(GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().format.format);
		m_AttachmentInfos.emplace_back(attachmentInfo);
		m_ColorBlends.emplace_back(colorBlend);
		
		StoreExtent(GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().surfaceSize);
	}

	void RenderPass2::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE
		
		VkClearValue                                  clearValue{};
		clearValue.color                            = { 0.0f, 0.0f, 0.0f, 1.0f };
		
		VkRenderingAttachmentInfo                     attachmentInfo{};
		attachmentInfo.sType                        = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
		attachmentInfo.imageView                    = renderTarget->GetRHIImpl<RenderTarget>()->GetView();
		attachmentInfo.imageLayout                  = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL;
		attachmentInfo.loadOp                       = ToVkAttachmentLoadOp(info.loadOp);
		attachmentInfo.storeOp                      = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentInfo.clearValue                   = clearValue;
		
		if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IUnifiedImageLayouts>())
		{
			attachmentInfo.imageLayout              = VK_IMAGE_LAYOUT_GENERAL;
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
		
		m_ColorAttachmentFormats.emplace_back(ToVkFormat(renderTarget->GetFormat()));
		m_AttachmentInfos.emplace_back(attachmentInfo);
		m_ColorBlends.emplace_back(colorBlend);
		
		StoreExtent({ renderTarget->GetWidth(), renderTarget->GetHeight() });
	}

	void RenderPass2::BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (m_SwapChainImageIndex)
		{
			m_AttachmentInfos[*m_SwapChainImageIndex].imageView = GetContext().Get<ISwapChain>()->GetView(frameBufferIndex);
		}
		
		VkRenderingInfo                           info{};
		info.sType                              = VK_STRUCTURE_TYPE_RENDERING_INFO;
		info.renderArea                      = {  { 0, 0 }, *m_Extent };
		info.layerCount                         = 1;
		info.colorAttachmentCount               = static_cast<uint32_t>(m_AttachmentInfos.size());
		info.pColorAttachments                  = m_AttachmentInfos.data();
		
		commandBuffer->BeginRendering(info);
	}
	
	void RenderPass2::EndRenderPass(const Unit::CommandBuffer* commandBuffer) const
	{
		NEPTUNE_PROFILE_ZONE
		
		commandBuffer->EndRendering();
	}
	
	VkPipelineRenderingCreateInfo* RenderPass2::GetRenderingInfo()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderingInfo.sType                                    = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
		m_RenderingInfo.colorAttachmentCount                     = static_cast<uint32_t>(m_ColorAttachmentFormats.size());
		m_RenderingInfo.pColorAttachmentFormats                  = m_ColorAttachmentFormats.data();
		
		return &m_RenderingInfo;
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