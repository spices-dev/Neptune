/**
* @file FragmentShaderInterlock.cpp.
* @brief The FragmentShaderInterlock Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "FragmentShaderInterlock.h"

namespace Neptune::OpenGL::Extension {

    FragmentShaderInterlock::FragmentShaderInterlock(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_fragment_shader_interlock");
    }

}

#endif