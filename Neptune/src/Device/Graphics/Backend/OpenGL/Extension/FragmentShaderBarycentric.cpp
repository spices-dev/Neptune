/**
* @file FragmentShaderBarycentric.cpp.
* @brief The FragmentShaderBarycentric Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "FragmentShaderBarycentric.h"

namespace Neptune::OpenGL::Extension {

    FragmentShaderBarycentric::FragmentShaderBarycentric(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddExtensions("GL_NV_fragment_shader_barycentric");
    }

}

#endif