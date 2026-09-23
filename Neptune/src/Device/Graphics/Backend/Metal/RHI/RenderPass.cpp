/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "RenderPass.h"

namespace Neptune::Metal {

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE
	}

	void RenderPass::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE
	}

	void RenderPass::BeginRenderPass(const Unit::CommandEncoder* commandEncoder)
	{
		NEPTUNE_PROFILE_ZONE
	}

	void RenderPass::EndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
}

#endif