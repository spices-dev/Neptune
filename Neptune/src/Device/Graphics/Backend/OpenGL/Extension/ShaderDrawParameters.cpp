/**
* @file ShaderDrawParameters.cpp.
* @brief The ShaderDrawParameters Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShaderDrawParameters.h"

namespace Neptune::OpenGL::Extension {

    ShaderDrawParameters::ShaderDrawParameters(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddExtensions("GL_ARB_draw_parameters");
    }

}

#endif