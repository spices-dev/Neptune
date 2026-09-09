/**
* @file Debug.cpp.
* @brief The Debug Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Debug.h"

namespace Neptune::OpenGL::Capability {

    Debug::Debug(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        // New
        AddExtensions("GL_KHR_debug");
        
        // Old
        AddExtensions("GL_ARB_debug_output");
        
        // TODO
    }

}

#endif