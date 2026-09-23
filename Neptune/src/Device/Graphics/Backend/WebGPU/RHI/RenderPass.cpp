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

namespace Neptune::WebGPU {

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE
		
		WGPURenderPassColorAttachment                 attachment{};
		attachment.depthSlice                       = WGPU_DEPTH_SLICE_UNDEFINED;
		attachment.loadOp                           = WGPULoadOp_Clear;
		attachment.storeOp                          = WGPUStoreOp_Store;
		attachment.clearValue                       = { 1.0, 0.0, 0.0, 1.0 };
		attachment.view                             = nullptr;
		
		m_SurfaceIndex = m_Attachments.size();
		m_Attachments.emplace_back(attachment);
	}

	void RenderPass::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void RenderPass::BeginRenderPass(const Unit::CommandEncoder* commandEncoder)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (m_SurfaceIndex)
		{
			WGPUSurfaceTexture swapChainTexture;
			wgpuSurfaceGetCurrentTexture(GetContext().Get<ISurface>()->Handle(), &swapChainTexture);

			WGPUTextureViewDescriptor      desc{};
			desc.dimension               = WGPUTextureViewDimension_2D;
			desc.baseMipLevel            = 0;
			desc.mipLevelCount           = 1;
			desc.baseArrayLayer          = 0;
			desc.arrayLayerCount         = 1;
			desc.aspect                  = WGPUTextureAspect_Undefined;
			desc.usage                   = WGPUTextureUsage_RenderAttachment;
			
			m_SurfaceView = CreateUP<Unit::TextureView>();
			
			m_SurfaceView->CreateTextureView(swapChainTexture.texture, desc);
			
			DEBUGUTILS_SETOBJECTNAME(*m_SurfaceView, "SurfaceTextureView")
			
			m_Attachments[*m_SurfaceIndex].view = m_SurfaceView->GetHandle();
		}
		
		WGPURenderPassDescriptor                      desc{};
		desc.colorAttachmentCount                   = m_Attachments.size();
		desc.colorAttachments                       = m_Attachments.data();
		desc.depthStencilAttachment                 = nullptr;
		
		m_RenderPass = CreateUP<Unit::RenderPassEncoder>();
		
		m_RenderPass->SetHandle(commandEncoder->BeginRenderPass(desc));
		
		DEBUGUTILS_SETOBJECTNAME(*m_RenderPass, "RenderPassEncoder")
	}

	void RenderPass::EndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderPass->EndRenderPass();
	}
	
}

#endif