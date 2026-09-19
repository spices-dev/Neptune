/**
* @file RenderPass2.cpp.
* @brief The RenderPass2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderPass3.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/SwapChain.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/Vulkan/Unit/CommandBuffer.h"

namespace Neptune::Vulkan::Middleware {
	
	RenderPass3::RenderPass3(Context& context)
		: ContextAccessor(context)
		, m_ImageLayout(IImageLayout::Create(context))
		, m_Synchronization(ISynchronization::Create(context))
	{}

	void RenderPass3::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE
		
		VkClearValue                                  clearValue{};
		clearValue.color                            = { 0.0f, 0.0f, 0.0f, 1.0f };
		
		VkRenderingAttachmentInfo                     attachmentInfo{};
		attachmentInfo.sType                        = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
		attachmentInfo.imageView                    = VK_NULL_HANDLE;
		attachmentInfo.imageLayout                  = m_ImageLayout->From(VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL);
		attachmentInfo.loadOp                       = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachmentInfo.storeOp                      = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentInfo.clearValue                   = clearValue;
		
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
		
		{
			VkImageMemoryBarrier2                     barrier{};
			barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
			barrier.srcStageMask                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.srcAccessMask                   = VK_ACCESS_2_NONE;
			barrier.dstStageMask                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.dstAccessMask                   = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
			barrier.oldLayout                       = m_ImageLayout->From(VK_IMAGE_LAYOUT_UNDEFINED);
			barrier.newLayout                       = m_ImageLayout->From(VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL);
			barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.image                           = VK_NULL_HANDLE;
			barrier.subresourceRange                = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
			
			m_AttachmentInBarriers.emplace_back(barrier);
		}
		
		{
			VkImageMemoryBarrier2                     barrier{};
			barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
			barrier.srcStageMask                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.srcAccessMask                   = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
			barrier.dstStageMask                    = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT;
			barrier.dstAccessMask                   = VK_ACCESS_2_NONE;
			barrier.oldLayout                       = m_ImageLayout->From(VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL);
			barrier.newLayout                       = m_ImageLayout->From(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
			barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.image                           = VK_NULL_HANDLE;
			barrier.subresourceRange                = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
			
			m_AttachmentOutBarriers.emplace_back(barrier);
		}
		
		m_SwapChainImageIndex = m_AttachmentInfos.size();
		m_ColorAttachmentFormats.emplace_back(GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().format.format);
		m_AttachmentInfos.emplace_back(attachmentInfo);
		m_ColorBlends.emplace_back(colorBlend);
		
		StoreExtent(GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().surfaceSize);
	}

	void RenderPass3::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE
		
		VkClearValue                                  clearValue{};
		clearValue.color                            = { 0.0f, 0.0f, 0.0f, 1.0f };
		
		VkRenderingAttachmentInfo                     attachmentInfo{};
		attachmentInfo.sType                        = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
		attachmentInfo.imageView                    = renderTarget->GetRHIImpl<RenderTarget>()->GetView();
		attachmentInfo.imageLayout                  = m_ImageLayout->From(VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL);
		attachmentInfo.loadOp                       = ToVkAttachmentLoadOp(info.loadOp);
		attachmentInfo.storeOp                      = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentInfo.clearValue                   = clearValue;
		
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
		
		{
			VkImageMemoryBarrier2                     barrier{};
			barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
			barrier.srcStageMask                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.srcAccessMask                   = VK_ACCESS_2_NONE;
			barrier.dstStageMask                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.dstAccessMask                   = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
			barrier.oldLayout                       = m_ImageLayout->From(ToVkImageLayout(info.inLayout));
			barrier.newLayout                       = m_ImageLayout->From(VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL);
			barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.image                           = renderTarget->GetRHIImpl<RenderTarget>()->Handle();
			barrier.subresourceRange                = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
			
			m_AttachmentInBarriers.emplace_back(barrier);
		}
		
		{
			VkImageMemoryBarrier2                     barrier{};
			barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
			barrier.srcStageMask                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.srcAccessMask                   = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
			barrier.dstStageMask                    = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT;
			barrier.dstAccessMask                   = VK_ACCESS_2_NONE;
			barrier.oldLayout                       = m_ImageLayout->From(VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL);
			barrier.newLayout                       = m_ImageLayout->From(ToVkImageLayout(info.outLayout));
			barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.image                           = renderTarget->GetRHIImpl<RenderTarget>()->Handle();
			barrier.subresourceRange                = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
			
			m_AttachmentOutBarriers.emplace_back(barrier);
		}
		
		m_ColorAttachmentFormats.emplace_back(ToVkFormat(renderTarget->GetFormat()));
		m_AttachmentInfos.emplace_back(attachmentInfo);
		m_ColorBlends.emplace_back(colorBlend);
		
		StoreExtent({ renderTarget->GetWidth(), renderTarget->GetHeight() });
	}

	void RenderPass3::BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (m_SwapChainImageIndex)
		{
			m_AttachmentInfos[*m_SwapChainImageIndex].imageView = GetContext().Get<ISwapChain>()->GetView(frameBufferIndex);
			
			m_AttachmentInBarriers[*m_SwapChainImageIndex].image = GetContext().Get<ISwapChain>()->GetImage(frameBufferIndex);

			m_AttachmentOutBarriers[*m_SwapChainImageIndex].image = GetContext().Get<ISwapChain>()->GetImage(frameBufferIndex);
		}
		
		std::ranges::for_each(m_AttachmentInBarriers, [&](const auto& barrier) {
			
			m_Synchronization->InsertBarrier(commandBuffer, barrier);
		});
		
		VkRenderingInfo                           info{};
		info.sType                              = VK_STRUCTURE_TYPE_RENDERING_INFO;
		info.renderArea                         = {  { 0, 0 }, *m_Extent };
		info.layerCount                         = 1;
		info.colorAttachmentCount               = static_cast<uint32_t>(m_AttachmentInfos.size());
		info.pColorAttachments                  = m_AttachmentInfos.data();
		
		commandBuffer->BeginRendering(info);
	}
	
	void RenderPass3::EndRenderPass(const Unit::CommandBuffer* commandBuffer) const
	{
		NEPTUNE_PROFILE_ZONE
		
		commandBuffer->EndRendering();
		
		std::ranges::for_each(m_AttachmentOutBarriers, [&](const auto& barrier) {
			
			m_Synchronization->InsertBarrier(commandBuffer, barrier);
		});
	}
	
	VkPipelineRenderingCreateInfo* RenderPass3::GetRenderingInfo()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderingInfo.sType                                    = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
		m_RenderingInfo.colorAttachmentCount                     = static_cast<uint32_t>(m_ColorAttachmentFormats.size());
		m_RenderingInfo.pColorAttachmentFormats                  = m_ColorAttachmentFormats.data();
		
		return &m_RenderingInfo;
	}
	
	const VkPipelineColorBlendStateCreateInfo& RenderPass3::GetColorBlendInfo()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_ColorBlendInfo.sType                                   = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		m_ColorBlendInfo.attachmentCount                         = static_cast<uint32_t>(m_ColorBlends.size());
		m_ColorBlendInfo.pAttachments                            = m_ColorBlends.data();
		
		return m_ColorBlendInfo;
	}
	
	void RenderPass3::StoreExtent(const VkExtent2D& extent)
	{
		NEPTUNE_PROFILE_ZONE

		if (m_Extent.has_value()) return;

		m_Extent = extent;
	}
	
}

#endif