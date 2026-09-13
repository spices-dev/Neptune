/**
* @file SeparateShaderObjects.cpp.
* @brief The SeparateShaderObjects Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "SeparateShaderObjects.h"

namespace Neptune::OpenGL::Extension {

    SeparateShaderObjects::SeparateShaderObjects(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_separate_shader_objects");
    }

}

#endif