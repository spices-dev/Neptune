/**
* @file Robustness.cpp.
* @brief The Robustness Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Robustness.h"

namespace Neptune::OpenGL::Extension {

    Robustness::Robustness(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddExtensions("GL_ARB_robustness");
    }
    
    void Robustness::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        GLint flags = 0;
        
        glGetIntegerv(GL_RESET_NOTIFICATION_STRATEGY, &m_ResetStrategy);
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        
        m_ContextRobust = (flags & GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT) != 0;
    }
    
    bool Robustness::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Robustness [ resetStrategy ] : " << m_ResetStrategy;
        NEPTUNE_LOG_CORE(I) << "Robustness [ contextRobust ] : " << m_ContextRobust;

        return true;
    }

}

#endif