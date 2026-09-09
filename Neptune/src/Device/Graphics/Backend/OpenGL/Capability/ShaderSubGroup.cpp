/**
* @file ShaderSubGroup.cpp.
* @brief The ShaderSubGroup Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShaderSubGroup.h"

namespace Neptune::OpenGL::Capability {

    ShaderSubGroup::ShaderSubGroup(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_NV_shader_subgroup");
        
        // TODO
    }

}

#endif