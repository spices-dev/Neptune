/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "RenderPass.h"

#include "Device/Graphics/Backend/WebGPU/Infrastructure/CommandEncoder.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Surface.h"
#include "Device/Graphics/Backend/WebGPU/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/WebGPU/Converter.h"
#include "Device/Graphics/Backend/WebGPU/RHI/Pipeline.h"

namespace Neptune::WebGPU {

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE
		
		WGPURenderPassColorAttachment                 attachment{};
		attachment.depthSlice                       = WGPU_DEPTH_SLICE_UNDEFINED;
		attachment.loadOp                           = WGPULoadOp_Clear;
		attachment.storeOp                          = WGPUStoreOp_Store;
		attachment.clearValue                       = { 0.0, 0.0, 0.0, 1.0 };
		attachment.view                             = nullptr;
		
		m_SurfaceIndex = m_Attachments.size();
		m_Attachments.emplace_back(attachment);
	}

	void RenderPass::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		WGPURenderPassColorAttachment                 attachment{};
		attachment.depthSlice                       = WGPU_DEPTH_SLICE_UNDEFINED;
		attachment.loadOp                           = ToWGPULoadOp(info.loadOp);
		attachment.storeOp                          = WGPUStoreOp_Store;
		attachment.clearValue                       = { 0.0, 0.0, 0.0, 1.0 };
		attachment.view                             = renderTarget->GetRHIImpl<RenderTarget>()->GetView();
		
		m_Attachments.emplace_back(attachment);
	}

	void RenderPass::BeginRenderPass(const Unit::CommandEncoder* commandEncoder)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (m_SurfaceIndex)
		{
			m_Attachments[*m_SurfaceIndex].view = GetContext().Get<ISurface>()->TextureView();
		}
		
		WGPURenderPassDescriptor                      desc{};
		desc.colorAttachmentCount                   = m_Attachments.size();
		desc.colorAttachments                       = m_Attachments.data();
		desc.depthStencilAttachment                 = nullptr;
		desc.occlusionQuerySet                      = nullptr;
		desc.timestampWrites                        = nullptr;
		
		m_RenderPass = CreateUP<Resource::PassEncoder>(GetContext());
		
		m_RenderPass->SetHandle(commandEncoder->BeginRenderPass(desc));
		
		DEBUGUTILS_SETOBJECTNAME(*m_RenderPass, "RenderPassEncoder")
	}
	
	void RenderPass::BeginComputePass(const Unit::CommandEncoder* commandEncoder)
	{
		NEPTUNE_PROFILE_ZONE
		
		WGPUComputePassDescriptor                     desc{};
		desc.timestampWrites                        = nullptr;
		
		m_RenderPass = CreateUP<Resource::PassEncoder>(GetContext());
		
		m_RenderPass->SetHandle(commandEncoder->BeginComputePass(desc));
		
		DEBUGUTILS_SETOBJECTNAME(*m_RenderPass, "ComputePassEncoder")
	}

	void RenderPass::EndPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderPass->EndPass();
	}

	void RenderPass::BindPipeline(const SP<RHI::Pipeline>& pipeline) const
	{
		NEPTUNE_PROFILE_ZONE
		
		auto rhi = pipeline->GetRHIImpl<Pipeline>();
		
		m_RenderPass->BindPipeline(rhi);
	}
	
	void RenderPass::BindDescriptorList(const DescriptorList* descriptorList) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderPass->BindBindGroup(descriptorList);
	}

	void RenderPass::UpdateShaderConstant(const void* data, uint32_t size, uint32_t offset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderPass->UpdateImmediates(offset, data, size);
	}
}

#endif