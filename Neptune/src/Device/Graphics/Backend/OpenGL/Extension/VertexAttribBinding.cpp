/**
* @file VertexAttribBinding.cpp.
* @brief The VertexAttribBinding Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "VertexAttribBinding.h"

namespace Neptune::OpenGL::Extension {

    VertexAttribBinding::VertexAttribBinding(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddExtensions("GL_ARB_vertex_attrib_binding");
        
        glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &m_MaxBindings);
        glGetIntegerv(GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET, &m_MaxRelativeOffset);
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &m_MaxAttribs);
    }

}

#endif