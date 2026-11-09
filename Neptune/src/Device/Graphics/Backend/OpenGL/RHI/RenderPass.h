/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/OpenGL/Unit/FrameBuffer.h"
#include "Device/Graphics/Backend/OpenGL/Unit/RenderBuffer.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"

namespace Neptune::OpenGL {

	/**
	* @brief OpenGL::RenderPass Class.
	* This class defines the OpenGL::RenderPass behaves.
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
		void Build(uint32_t count = MaxFrameInFlight) override;

	public:
		
		/**
		* @brief Begin RenderPass.
		* 
		* @param[in] frameBufferIndex .
		* 
		*/
		void BeginRenderPass(uint32_t frameBufferIndex) const;
		
		/**
		* @brief End RenderPass.
		*/
		void EndRenderPass() const;
		
	private:

		std::vector<UP<Unit::FrameBuffer>>       m_FrameBuffers;                    // @brief FrameBuffer.
		std::vector<GLuint>                      m_Attachments;                     // @brief Container of Attachment.
		bool                                     m_UseSwapChain = false;            // @brief Container of Attachment.

	};
}

#endif