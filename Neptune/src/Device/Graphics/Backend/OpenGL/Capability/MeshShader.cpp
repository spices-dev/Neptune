/**
* @file MeshShader.cpp.
* @brief The MeshShader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "MeshShader.h"

namespace Neptune::OpenGL::Capability {

    MeshShader::MeshShader(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_NV_mesh_shader");
        
        // TODO
    }

}

#endif