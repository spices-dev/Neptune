/**
* @file ParallelShaderCompile.cpp.
* @brief The ParallelShaderCompile Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ParallelShaderCompile.h"

namespace Neptune::OpenGL::Capability {

    ParallelShaderCompile::ParallelShaderCompile(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_parallel_shader_compile");
    }

}

#endif