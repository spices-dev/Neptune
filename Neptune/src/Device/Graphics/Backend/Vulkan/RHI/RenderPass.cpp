/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DynamicRendering.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/RenderPass/RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/RenderPass/RenderPass2.h"

namespace Neptune::Vulkan {
	
	RenderPass::RenderPass(Context& context)
		: ContextAccessor(context)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IDynamicRendering>())
		{
			m_Interface = CreateUP<Middleware::RenderPass2>(context);
		}
		else
		{
			m_Interface = CreateUP<Middleware::RenderPass>(context);
		}
	}

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE

		m_Interface->AddSwapChainAttachment();
	}

	void RenderPass::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_Interface->AddColorAttachment(renderTarget, info);
	}

	void RenderPass::Build(uint32_t count)
	{
		NEPTUNE_PROFILE_ZONE

		m_Interface->Build(count);
	}

	void RenderPass::BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex) const
	{
		NEPTUNE_PROFILE_ZONE

		m_Interface->BeginRenderPass(commandBuffer, frameBufferIndex);
	}

	void RenderPass::EndRenderPass(const Unit::CommandBuffer* commandBuffer) const
	{
		NEPTUNE_PROFILE_ZONE

		m_Interface->EndRenderPass(commandBuffer);
	}
	
}

#endif