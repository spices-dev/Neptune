/**
* @file RenderTarget.cpp.
* @brief The RenderTarget Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "RenderTarget.h"
#include "Resource/Texture/RenderTarget.h"

namespace Neptune::OpenGL {

	void RenderTarget::CreateRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE
		
		CreateColorRenderTarget(info);
	}

	void* RenderTarget::CreateBindingID()
	{
		NEPTUNE_PROFILE_ZONE

		return nullptr;
	}

	bool RenderTarget::CopyToRenderTarget(const SP<RHI::RenderTarget>& target)
	{
		NEPTUNE_PROFILE_ZONE

		return false;
	}

	TextureFormat RenderTarget::GetFormat() const
	{
		NEPTUNE_PROFILE_ZONE

		return TextureFormat::RGBA8_UNORM;
	}

	void RenderTarget::CreateColorRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Texture = CreateUP<Resource::Texture>(GetContext());

		{
			m_Texture->CreateTexture(info);
		}

		{
			m_Texture->CreateSampler();
		}

		m_Texture->SetName("RenderTarget");
	}

	void RenderTarget::CreateDepthRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE
	}
}

#endif