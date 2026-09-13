/**
* @file ParallelShaderCompile.cpp.
* @brief The ParallelShaderCompile Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ParallelShaderCompile.h"

namespace Neptune::OpenGL::Extension {

    ParallelShaderCompile::ParallelShaderCompile(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_parallel_shader_compile");
    }

}

#endif