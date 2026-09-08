/**
* @file Spirv.cpp.
* @brief The Spirv Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Spirv.h"

namespace Neptune::OpenGL::Capability {

    Spirv::Spirv(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_gl_spirv");
        
        // TODO
    }

}

#endif