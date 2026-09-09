/**
* @file VertexAttribBinding.cpp.
* @brief The VertexAttribBinding Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "VertexAttribBinding.h"

namespace Neptune::OpenGL::Capability {

    VertexAttribBinding::VertexAttribBinding(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_ARB_vertex_attrib_binding");
        
        // TODO
    }

}

#endif