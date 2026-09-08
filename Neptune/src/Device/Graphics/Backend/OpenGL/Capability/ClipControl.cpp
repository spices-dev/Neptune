/**
* @file ClipControl.cpp.
* @brief The ClipControl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ClipControl.h"

namespace Neptune::OpenGL::Capability {

    ClipControl::ClipControl(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_clip_control");
        
        glClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);
    }

}

#endif