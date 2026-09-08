/**
* @file TextureBarrier.cpp.
* @brief The TextureBarrier Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TextureBarrier.h"

namespace Neptune::OpenGL::Capability {

    TextureBarrier::TextureBarrier(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_texture_barrier");
    }

}

#endif