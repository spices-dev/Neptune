/**
* @file ES32Compatibility.cpp.
* @brief The ES32Compatibility Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ES32Compatibility.h"

namespace Neptune::OpenGL::Capability {

    ES32Compatibility::ES32Compatibility(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_ARB_ES3_2_compatibility");
        AddExtensions("GL_ARB_ES3_1_compatibility");
        AddExtensions("GL_ARB_ES3_compatibility");
        AddExtensions("GL_ARB_ES2_compatibility");
    }

}

#endif