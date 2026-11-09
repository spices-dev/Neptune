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
#include "Device/Graphics/Backend/WebGPU/Resource/PassEncoder.h"

namespace Neptune::WebGPU::Unit {
	
	class CommandEncoder;
}

namespace Neptune::WebGPU {

	class DescriptorList;
	
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
		* @brief Begin Compute.
		* 
		* @param[in] commandEncoder CommandEncoder.
		*/
		void BeginComputePass(const Unit::CommandEncoder* commandEncoder);
		
		/**
		* @brief End Pass.
		*/
		void EndPass() const;
		
		/**
		* @brief Get PassEncoder Unit Handle.
		*
		* @tparam T PassEncoder Unit
		* 
		* @return Returns PassEncoder Unit Handle.
		*/
		template<IsUnit T>
		T::Handle Handle() const { return m_RenderPass->Handle<T>(); }
		
		/**
		* @brief Get PassEncoder Unit.
		*
		* @tparam T PassEncoder Unit
		* 
		* @return Returns PassEncoder Unit.
		*/
		template<IsUnit T>
		const UP<T>& IHandle() const { return m_RenderPass->IHandle<T>(); }
		
		/**
		* @brief Bind Pipeline.
		* 
		* @param[in] pipeline RHI::Pipeline
		*/
		void BindPipeline(const SP<RHI::Pipeline>& pipeline) const;
		
		/**
		* @brief Bind DescriptorList.
		* 
		* @param[in] descriptorList DescriptorList
		*/
		void BindDescriptorList(const DescriptorList* descriptorList) const;
		
		/**
		* @brief Update ShaderConstant.
		*
		* @param[in] data ShaderConstant data.
		* @param[in] size ShaderConstant size.
		* @param[in] offset ShaderConstant offset.
		*/
		void UpdateShaderConstant(const void* data, uint32_t size, uint32_t offset = 0) const;
		
	private:
		
		UP<Resource::PassEncoder>                  m_RenderPass;             // @brief This RenderPass.
		std::vector<WGPURenderPassColorAttachment> m_Attachments;            // @brief WGPURenderPassColorAttachment.
		std::optional<uint32_t>                    m_SurfaceIndex;           // @brief Surface Index.
		
	};
}

#endif