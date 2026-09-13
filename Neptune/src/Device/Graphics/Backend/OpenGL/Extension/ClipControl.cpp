/**
* @file ClipControl.cpp.
* @brief The ClipControl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ClipControl.h"

namespace Neptune::OpenGL::Extension {

    ClipControl::ClipControl(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_clip_control");
        
        glClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);
    }

}

#endif