/**
* @file TextureFilterAnisotropic.cpp.
* @brief The TextureFilterAnisotropic Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TextureFilterAnisotropic.h"

namespace Neptune::OpenGL::Capability {

    TextureFilterAnisotropic::TextureFilterAnisotropic(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_texture_filter_anisotropic");
        
        // TODO
    }

}

#endif