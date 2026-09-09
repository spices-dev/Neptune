/**
* @file BindlessTexture.cpp.
* @brief The BindlessTexture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "BindlessTexture.h"

namespace Neptune::OpenGL::Capability {

    BindlessTexture::BindlessTexture(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_bindless_texture");
    }

}

#endif