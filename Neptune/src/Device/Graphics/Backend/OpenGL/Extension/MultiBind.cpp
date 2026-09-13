/**
* @file MultiBind.cpp.
* @brief The MultiBind Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "MultiBind.h"

namespace Neptune::OpenGL::Extension {

    MultiBind::MultiBind(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_multi_bind");
    }

    void MultiBind::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_MaxTextureUnits);
        glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &m_MaxUniformBinding);
    }
    
    bool MultiBind::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "MultiBind [ maxTextureUnits ] : " << m_MaxTextureUnits;
        NEPTUNE_LOG_CORE(I) << "MultiBind [ maxUniformBinding ] : " << m_MaxUniformBinding;

        return true;
    }
    
}

#endif