/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"
#include "Device/Graphics/Backend/WebGPU/Unit/RenderPassEncoder.h"
#include "Device/Graphics/Backend/WebGPU/Unit/TextureView.h"

namespace Neptune::WebGPU::Unit {
	
	class CommandEncoder;
}

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::WebGPU {

	/**
	* @brief WebGPU::RenderPass Class.
	* This class defines the WebGPU::RenderPass behaves.
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
		
		/**
		* @brief Interface Get RenderPassEncoder Handle.
		* 
		* @return Returns RenderPassEncoder Handle.
		*/
		Unit::RenderPassEncoder::Handle Handle() const { return m_RenderPass->GetHandle(); }
		
		/**
		* @brief Interface Get RenderPassEncoder.
		* 
		* @return Returns RenderPassEncoder.
		*/
		const UP<Unit::RenderPassEncoder>& IHandle() const { return m_RenderPass; }
		
	private:
		
		UP<Unit::RenderPassEncoder>                m_RenderPass;             // @brief This RenderPass.
		std::vector<WGPURenderPassColorAttachment> m_Attachments;            // @brief WGPURenderPassColorAttachment.
		std::optional<uint32_t>                    m_SurfaceIndex;           // @brief Surface Index.
		
	};
}

#endif