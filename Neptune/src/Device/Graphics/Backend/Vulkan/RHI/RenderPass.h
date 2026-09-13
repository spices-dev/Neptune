/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/RenderPass/IRenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Unit/RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Unit/FrameBuffer.h"
#include "Device/Graphics/Backend/Vulkan/Unit/CommandBuffer.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"

#include <vector>
#include <optional>

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::RenderPass Class.
	* This class defines the Vulkan::RenderPass behaves.
	*/
	class RenderPass : public ContextAccessor, public RHI::RHIRenderPass::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit RenderPass(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~RenderPass() override = default;

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
		void Build(uint32_t count = MaxFrameInFlight) override;

	public:

		/**
		* @brief Begin RenderPass.
		*
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] frameBufferIndex .
		*/
		void BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex) const;

		/**
		* @brief Interface of End RenderPass.
		* 
		* @param[in] commandBuffer CommandBuffer.
		*/
		void EndRenderPass(const Unit::CommandBuffer* commandBuffer) const;

		/**
		* @brief Get Middleware.
		* 
		* @return Returns Middleware.
		*/
		const UP<Middleware::IRenderPass>& GetMiddleware() const { return m_Interface; }
		
	private:

		UP<Middleware::IRenderPass> m_Interface; // @brief IRenderPass.
	};
}

#endif