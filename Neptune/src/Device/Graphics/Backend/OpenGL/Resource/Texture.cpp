/**
* @file Texture.cpp.
* @brief The Texture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Texture.h"
#include "Device/Graphics/Backend/OpenGL/Converter.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/DebugUtilsObject.h"

namespace Neptune::OpenGL::Resource {

	void Texture::SetTexture(Unit::Texture::Handle texture)
	{
		NEPTUNE_PROFILE_ZONE

		m_Texture.SetHandle(texture);

		DEBUGUTILS_SETOBJECTNAME(m_Texture, "Texture")
	}

	void Texture::CreateTexture(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_Format            = ToGLInternalFormat(info.format);
		m_LayerCount        = 1;
		m_Width             = info.width;
		m_Height            = info.height;
		
		m_Texture.CreateTexture();

		glTextureStorage2D(m_Texture.GetHandle(), 1, m_Format, m_Width, m_Height);
		
		glTextureParameteri(m_Texture.GetHandle(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Texture.GetHandle(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_Texture.GetHandle(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Texture.GetHandle(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		DEBUGUTILS_SETOBJECTNAME(m_Texture, "Texture")
	}
	
	void Texture::CreateSampler()
	{
		NEPTUNE_PROFILE_ZONE

		m_TextureSampler.CreateSampler();

		DEBUGUTILS_SETOBJECTNAME(m_TextureSampler, "Sampler")
	}

	void Texture::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Texture,        name + "Texture")
		DEBUGUTILS_SETOBJECTNAME(m_TextureSampler, name + "Sampler")
	}
}

#endif