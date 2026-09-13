/**
* @file RenderPass2.h.
* @brief The RenderPass2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "IRenderPass.h"

namespace Neptune::Vulkan::Middleware {
	
	/**
	* @brief Implement of Dynamic Rendering.
	*/
	class RenderPass2 : public ContextAccessor, public IRenderPass
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit RenderPass2(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~RenderPass2() override = default;

	public:

		/**
		* @brief Interface of Add SwapChain Attachment.
		*/
		void AddSwapChainAttachment() override;

		/**
		* @brief Interface of Add Color Attachment.
		*
		* @param[in] renderTarget RenderTarget.
		* @param[in] info RenderTargetAttachmentInfo.
		*/
		void AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info) override;

		/**
		* @brief Interface of Build RenderPass.
		*
		* @param[in] count Flight Frames.
		*/
		void Build(uint32_t count) override {}

		/**
		* @brief Begin RenderPass.
		*
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] frameBufferIndex .
		*/
		void BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex) override;
		
		/**
		* @brief Interface of End RenderPass.
		* 
		* @param[in] commandBuffer CommandBuffer.
		*/
		void EndRenderPass(const Unit::CommandBuffer* commandBuffer) const override;

		/**
		* @brief Get VkRenderPass Handle.
		* 
		* @return Returns VkRenderPass Handle.
		*/
		VkRenderPass Handle() const override { return VK_NULL_HANDLE; }
		
		/**
		* @brief Get VkPipelineRenderingCreateInfo.
		* 
		* @return Returns VkPipelineRenderingCreateInfo.
		*/
		VkPipelineRenderingCreateInfo* GetRenderingInfo() override;
		
		/**
		* @brief Get VkPipelineColorBlendStateCreateInfo.
		* 
		* @return Returns VkPipelineColorBlendStateCreateInfo.
		*/
		const VkPipelineColorBlendStateCreateInfo& GetColorBlendInfo() override;
		
	private:

		/**
		* @brief Store Extent.
		*
		* @param[in] extent VkExtent2D.
		*/
		void StoreExtent(const VkExtent2D& extent);
		
	private:
		
		std::vector<VkFormat>                             m_ColorAttachmentFormats;          // @brief VkFormat.
		VkPipelineColorBlendStateCreateInfo               m_ColorBlendInfo{};		   	     // @brief VkPipelineColorBlendStateCreateInfo.
		VkPipelineRenderingCreateInfo                     m_RenderingInfo{};                 // @brief VkPipelineRenderingCreateInfo.
		std::vector<VkRenderingAttachmentInfo>            m_AttachmentInfos;           	     // @brief VkRenderingAttachmentInfo.
		std::vector<VkPipelineColorBlendAttachmentState>  m_ColorBlends;					 // @brief VkPipelineColorBlendAttachmentState.
		std::optional<VkExtent2D>                         m_Extent;							 // @brief VkExtent2D.
	};
}

#endif