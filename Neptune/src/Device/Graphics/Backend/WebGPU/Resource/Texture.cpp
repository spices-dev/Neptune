/**
* @file Texture.cpp.
* @brief The Texture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Texture.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"

namespace Neptune::WebGPU::Resource {

	void Texture::SetTexture(Unit::Texture::Handle texture)
	{
		NEPTUNE_PROFILE_ZONE

		m_Texture.SetHandle(texture);

		DEBUGUTILS_SETOBJECTNAME(m_Texture, "Texture")
	}

	void Texture::CreateTextureView(const WGPUTextureViewDescriptor& desc)
	{
		NEPTUNE_PROFILE_ZONE

		assert(m_Texture.GetHandle());

		m_TextureView.CreateTextureView(m_Texture.GetHandle(), desc);

		DEBUGUTILS_SETOBJECTNAME(m_TextureView, "TextureView")
	}

	void Texture::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Texture,        name + "Texture")
		DEBUGUTILS_SETOBJECTNAME(m_TextureView,    name + "TextureView")
		DEBUGUTILS_SETOBJECTNAME(m_TextureSampler, name + "Sampler")
	}
}

#endif