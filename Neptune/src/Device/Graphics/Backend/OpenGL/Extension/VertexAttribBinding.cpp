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
    }

    void VertexAttribBinding::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &m_MaxBindings);
        glGetIntegerv(GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET, &m_MaxRelativeOffset);
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &m_MaxAttribs);
    }
    
    bool VertexAttribBinding::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "VertexAttribBinding [ maxBindings ] : " << m_MaxBindings;
        NEPTUNE_LOG_CORE(I) << "VertexAttribBinding [ maxRelativeOffset ] : " << m_MaxRelativeOffset;
        NEPTUNE_LOG_CORE(I) << "VertexAttribBinding [ maxAttribs ] : " << m_MaxAttribs;

        return true;
    }
    
}

#endif