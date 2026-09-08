/**
* @file ShaderDrawParameters.cpp.
* @brief The ShaderDrawParameters Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShaderDrawParameters.h"

namespace Neptune::OpenGL::Capability {

    ShaderDrawParameters::ShaderDrawParameters(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_draw_parameters");
    }

}

#endif