/**
* @file ShaderInt64.cpp.
* @brief The ShaderInt64 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShaderInt64.h"

namespace Neptune::OpenGL::Capability {

    ShaderInt64::ShaderInt64(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_gpu_shader_int64");
    }

}

#endif