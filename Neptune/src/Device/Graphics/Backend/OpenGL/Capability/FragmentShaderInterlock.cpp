/**
* @file FragmentShaderInterlock.cpp.
* @brief The FragmentShaderInterlock Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "FragmentShaderInterlock.h"

namespace Neptune::OpenGL::Capability {

    FragmentShaderInterlock::FragmentShaderInterlock(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_fragment_shader_interlock");
    }

}

#endif