/**
* @file TextureView.cpp.
* @brief The TextureView Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TextureView.h"

namespace Neptune::OpenGL::Extension {

    TextureView::TextureView(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_texture_view");
    }

}

#endif