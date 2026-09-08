/**
* @file TextureView.cpp.
* @brief The TextureView Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TextureView.h"

namespace Neptune::OpenGL::Capability {

    TextureView::TextureView(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_texture_view");
    }

}

#endif