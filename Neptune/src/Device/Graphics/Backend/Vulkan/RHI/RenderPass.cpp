/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderPass.h"

namespace Neptune::Vulkan {
	
	RenderPass::RenderPass(Context& context)
		: ContextAccessor(context)
		, m_RenderPass(Middleware::IRenderPass::Create(context))
	{}

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass->AddSwapChainAttachment();
	}

	void RenderPass::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass->AddColorAttachment(renderTarget, info);
	}

	void RenderPass::Build(uint32_t count)
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass->Build(count);
	}

	void RenderPass::BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex) const
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass->BeginRenderPass(commandBuffer, frameBufferIndex);
	}

	void RenderPass::EndRenderPass(const Unit::CommandBuffer* commandBuffer) const
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass->EndRenderPass(commandBuffer);
	}
	
}

#endif