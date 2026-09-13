/**
* @file TextureFilterAnisotropic.cpp.
* @brief The TextureFilterAnisotropic Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TextureFilterAnisotropic.h"

namespace Neptune::OpenGL::Extension {

    TextureFilterAnisotropic::TextureFilterAnisotropic(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_texture_filter_anisotropic");
    }

    void TextureFilterAnisotropic::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &m_MaxAnisotropy);
    }
    
    bool TextureFilterAnisotropic::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "TextureFilterAnisotropic [ maxAnisotropy ] : " << m_MaxAnisotropy;

        return true;
    }
    
}

#endif