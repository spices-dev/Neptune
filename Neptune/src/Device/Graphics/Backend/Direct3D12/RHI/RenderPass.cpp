/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "RenderPass.h"
#include "Device/Graphics/Backend/Direct3D12/Converter.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/Pipeline.h"

namespace Neptune::Direct3D12 {

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void RenderPass::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		D3D12_RENDER_PASS_RENDER_TARGET_DESC                  attachment{};
		//attachment.cpuDescriptor                            = rtvHandle0; 
		attachment.BeginningAccess.Type                     = ToD3D12RenderPassBeginAccessType(info.loadOp);
		attachment.BeginningAccess.Clear.ClearValue         = { .Color{ 0.0, 0.0, 0.0, 1.0 } };
		attachment.EndingAccess.Type                        = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE;
		
		m_Attachments.emplace_back(attachment);
	}

	void RenderPass::BeginRenderPass(Unit::GraphicsCommandList::Handle commandList) const
	{
		NEPTUNE_PROFILE_ZONE
		
		commandList->BeginRenderPass(m_Attachments.size(), m_Attachments.data(), nullptr, D3D12_RENDER_PASS_FLAG_NONE);
	}
	
	void RenderPass::EndPass(Unit::GraphicsCommandList::Handle commandList) const
	{
		NEPTUNE_PROFILE_ZONE
		
		commandList->EndRenderPass();
	}
}

#endif