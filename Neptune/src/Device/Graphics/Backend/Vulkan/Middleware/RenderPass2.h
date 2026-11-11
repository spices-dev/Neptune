/**
* @file RenderPass2.h.
* @brief The RenderPass2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Unit/FrameBuffer.h"
#include "IRenderPass.h"

namespace Neptune::Vulkan::Middleware {
	
	/**
	* @brief Implement of Classic RenderPass and FrameBuffer.
	*/
	class RenderPass2 : public ContextAccessor, public IRenderPass
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit RenderPass2(Context& context);

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
		void Build(uint32_t count) override;

		/**
		* @brief Interface Begin RenderPass.
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
		* @brief Interface Get VkRenderPass Handle.
		* 
		* @return Returns VkRenderPass Handle.
		*/
		VkRenderPass Handle() const override { return m_RenderPass.GetHandle(); }
		
		/**
		* @brief Interface Get VkPipelineRenderingCreateInfo.
		* 
		* @return Returns VkPipelineRenderingCreateInfo.
		*/
		VkPipelineRenderingCreateInfo* GetRenderingInfo() override { return nullptr; }
		
		/**
		* @brief Interface Get VkPipelineColorBlendStateCreateInfo.
		* 
		* @return Returns VkPipelineColorBlendStateCreateInfo.
		*/
		const VkPipelineColorBlendStateCreateInfo& GetColorBlendInfo() override;
		
	public:

		/**
		* @brief Get ColorBlends.
		*
		* @return Returns VkPipelineColorBlendAttachmentState.
		*/
		const std::vector<VkPipelineColorBlendAttachmentState>& GetColorBlends() const { return m_ColorBlends; }
		
	private:

		/**
		* @brief Store Extent.
		*
		* @param[in] extent VkExtent2D.
		*/
		void StoreExtent(const VkExtent2D& extent);

	private:

		Unit::RenderPass                                  m_RenderPass;                      // @brief This RenderPass.
		std::vector<SP<Unit::FrameBuffer>>                m_FrameBuffers;                    // @brief Container of FrameBuffer.

		VkPipelineColorBlendStateCreateInfo               m_ColorBlendInfo{};				 // @brief VkPipelineColorBlendStateCreateInfo.
		std::vector<VkAttachmentDescription2>             m_AttachmentDescriptions;          // @brief VkAttachmentDescription2.
		std::vector<VkAttachmentReference2>               m_ColorAttachmentReference;        // @brief VkAttachmentReference2.
		std::vector<VkPipelineColorBlendAttachmentState>  m_ColorBlends;					 // @brief VkPipelineColorBlendAttachmentState.
		std::vector<VkClearValue>                         m_ClearValues;					 // @brief VkClearValue.
		std::vector<VkImageView>                          m_ImageViews;						 // @brief VkImageView.
		class IImageLayout*                               m_ImageLayout;		        	 // @brief IImageLayout.
		std::optional<VkExtent2D>                         m_Extent;							 // @brief VkExtent2D.
	};
}

#endif