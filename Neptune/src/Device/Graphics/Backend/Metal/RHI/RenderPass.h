/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Device/Graphics/Backend/Metal/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"

namespace Neptune::Metal::Unit {
	
	class CommandEncoder;
}

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::Metal {

	/**
	* @brief Metal::RenderPass Class.
	* This class defines the Metal::RenderPass behaves.
	*/
	class RenderPass : public ContextAccessor, public RHI::RHIRenderPass::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit RenderPass(Context& context) : ContextAccessor(context) {}

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
		void Build(uint32_t count = MaxFrameInFlight) override {}

	public:

		/**
		* @brief Begin RenderPass.
		* 
		* @param[in] commandEncoder CommandEncoder.
		*/
		void BeginRenderPass(const Unit::CommandEncoder* commandEncoder);
		
		/**
		* @brief End RenderPass.
		*/
		void EndRenderPass() const;
		
	};
}

#endif