/**
* @file Texture.cpp.
* @brief The Texture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Texture.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"

namespace Neptune::WebGPU::Resource {

	void Texture::SetTexture(Unit::Texture::Handle texture)
	{
		NEPTUNE_PROFILE_ZONE

		m_Texture.SetHandle(texture);

		DEBUGUTILS_SETOBJECTNAME(m_Texture, "Texture")
	}

	void Texture::CreateTexture(const WGPUTextureDescriptor& desc)
	{
		NEPTUNE_PROFILE_ZONE

		m_Format     = desc.format;
		m_LayerCount = desc.size.depthOrArrayLayers;
		m_Width      = desc.size.width;
		m_Height     = desc.size.height;
		
		m_Texture.CreateTexture(GetContext().Get<IDevice>()->Handle(), desc);

		DEBUGUTILS_SETOBJECTNAME(m_Texture, "Texture")
	}
	
	void Texture::CreateTextureView(const WGPUTextureViewDescriptor& desc)
	{
		NEPTUNE_PROFILE_ZONE

		assert(m_Texture.GetHandle());

		m_TextureView.CreateTextureView(m_Texture.GetHandle(), desc);

		DEBUGUTILS_SETOBJECTNAME(m_TextureView, "TextureView")
	}
	
	void Texture::CreateSampler(const WGPUSamplerDescriptor& desc)
	{
		NEPTUNE_PROFILE_ZONE

		m_TextureSampler.CreateSampler(GetContext().Get<IDevice>()->Handle(), desc);

		DEBUGUTILS_SETOBJECTNAME(m_TextureSampler, "Sampler")
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