/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "RenderPass.h"

#include "Device/Graphics/Backend/OpenGL/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/DebugUtilsObject.h"

namespace Neptune::OpenGL {

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE

		m_UseSwapChain = true;
	}

	void RenderPass::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_Attachments.emplace_back(renderTarget->GetRHIImpl<RenderTarget>()->Handle());
	}

	void RenderPass::Build(uint32_t count)
	{
		NEPTUNE_PROFILE_ZONE

		if (m_UseSwapChain) return;
		
		std::vector<GLenum> drawBuffers(m_Attachments.size());
		
		for (size_t i = 0; i < m_Attachments.size(); ++i)
		{
			drawBuffers[i] = GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i);
		}
		
		for (uint32_t i = 0; i < count; i++)
		{
			auto frameBuffer = CreateUP<Unit::FrameBuffer>();

			frameBuffer->CreateFrameBuffer();

			for (size_t j = 0; j < m_Attachments.size(); ++j)
			{
				glNamedFramebufferTexture(frameBuffer->GetHandle(), GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(j), m_Attachments[j], 0);
			}
			
			glNamedFramebufferDrawBuffers(frameBuffer->GetHandle(), static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());
			
			GLenum status = glCheckNamedFramebufferStatus(frameBuffer->GetHandle(), GL_FRAMEBUFFER);
			
			if (status != GL_FRAMEBUFFER_COMPLETE) 
			{
				NEPTUNE_LOG_CORE(E) << "FrameBuffer incomplete, status = " << status;
			}

			DEBUGUTILS_SETOBJECTNAME(*frameBuffer, "FrameBuffer")
			
			m_FrameBuffers.emplace_back(std::move(frameBuffer));
		}
	}

	void RenderPass::BeginRenderPass(uint32_t frameBufferIndex) const
	{
		NEPTUNE_PROFILE_ZONE
		
		if (m_UseSwapChain)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffers[frameBufferIndex]->GetHandle());
		}
	}

	void RenderPass::EndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

#endif