/**
* @file IRenderPass.h.
* @brief The IRenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"

namespace Neptune {
	
	struct RenderTargetAttachmentInfo;
}

namespace Neptune::Vulkan::Unit {
	
	class CommandBuffer;
}

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::Vulkan::Middleware {
	
	/**
	* @brief Interface of RenderPass.
	*/
	class IRenderPass
	{
	public:

		/**
		* @brief Interface of Add SwapChain Attachment.
		*/
		virtual void AddSwapChainAttachment() = 0;

		/**
		* @brief Interface of Add Color Attachment.
		*
		* @param[in] renderTarget RenderTarget.
		* @param[in] info RenderTargetAttachmentInfo.
		*/
		virtual void AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info) = 0;

		/**
		* @brief Interface of Build RenderPass.
		*
		* @param[in] count Flight Frames.
		*/
		virtual void Build(uint32_t count) = 0;

		/**
		* @brief Interface of  Begin RenderPass.
		*
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] frameBufferIndex .
		*/
		virtual void BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex) = 0;
		
		/**
		* @brief Interface of End RenderPass.
		* 
		* @param[in] commandBuffer CommandBuffer.
		*/
		virtual void EndRenderPass(const Unit::CommandBuffer* commandBuffer) const = 0;
		
		/**
		* @brief Get VkRenderPass Handle.
		* 
		* @return Returns VkRenderPass Handle.
		*/
		virtual VkRenderPass Handle() const = 0;
		
		/**
		* @brief Get VkPipelineRenderingCreateInfo.
		* 
		* @return Returns VkPipelineRenderingCreateInfo.
		*/
		virtual VkPipelineRenderingCreateInfo* GetRenderingInfo() = 0;
		
		/**
		* @brief Get VkPipelineColorBlendStateCreateInfo.
		* 
		* @return Returns VkPipelineColorBlendStateCreateInfo.
		*/
		virtual const VkPipelineColorBlendStateCreateInfo& GetColorBlendInfo() = 0;
	};
}

#endif