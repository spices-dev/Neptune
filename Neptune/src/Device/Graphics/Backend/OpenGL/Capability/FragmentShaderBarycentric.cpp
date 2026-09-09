/**
* @file FragmentShaderBarycentric.cpp.
* @brief The FragmentShaderBarycentric Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "FragmentShaderBarycentric.h"

namespace Neptune::OpenGL::Capability {

    FragmentShaderBarycentric::FragmentShaderBarycentric(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_NV_fragment_shader_barycentric");
    }

}

#endif