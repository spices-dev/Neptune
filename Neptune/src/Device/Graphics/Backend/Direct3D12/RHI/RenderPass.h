/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/GraphicsCommandList.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"

namespace Neptune::Direct3D12::Unit {
	
	class CommandEncoder;
}

namespace Neptune::RHI {

	class RenderTarget;
	class Pipeline;
}

namespace Neptune::Direct3D12 {

	class DescriptorList;
	
	/**
	* @brief Direct3D12::RenderPass Class.
	* This class defines the Direct3D12::RenderPass behaves.
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
		* @param[in] commandList GraphicsCommandList.
		*/
		void BeginRenderPass(Unit::GraphicsCommandList::Handle commandList) const;
		
		/**
		* @brief End Pass.
		* 
		* @param[in] commandList GraphicsCommandList.
		*/
		void EndPass(Unit::GraphicsCommandList::Handle commandList) const;
		
	private:
		
		std::vector<D3D12_RENDER_PASS_RENDER_TARGET_DESC> m_Attachments; // @brief D3D12_RENDER_PASS_RENDER_TARGET_DESC.
	};
}

#endif