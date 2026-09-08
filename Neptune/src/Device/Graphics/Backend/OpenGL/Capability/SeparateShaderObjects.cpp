/**
* @file SeparateShaderObjects.cpp.
* @brief The SeparateShaderObjects Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "SeparateShaderObjects.h"

namespace Neptune::OpenGL::Capability {

    SeparateShaderObjects::SeparateShaderObjects(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_separate_shader_objects");
    }

}

#endif