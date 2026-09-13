/**
* @file BindlessTexture.cpp.
* @brief The BindlessTexture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "BindlessTexture.h"

namespace Neptune::OpenGL::Extension {

    BindlessTexture::BindlessTexture(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddExtensions("GL_ARB_bindless_texture");
    }

}

#endif