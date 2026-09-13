/**
* @file TextureBarrier.cpp.
* @brief The TextureBarrier Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TextureBarrier.h"

namespace Neptune::OpenGL::Extension {

    TextureBarrier::TextureBarrier(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_texture_barrier");
    }

}

#endif