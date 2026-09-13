/**
* @file Debug.cpp.
* @brief The Debug Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Debug.h"

namespace Neptune::OpenGL::Extension {

    Debug::Debug(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        // New
        AddExtensions("GL_KHR_debug");
        
        // Old
        // AddExtensions("GL_ARB_debug_output");
    }

    void Debug::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &m_MaxMessageLength);
        glGetIntegerv(GL_MAX_DEBUG_LOGGED_MESSAGES, &m_MaxLoggedMessages);
        glGetIntegerv(GL_MAX_DEBUG_GROUP_STACK_DEPTH, &m_MaxGroupStackDepth);
    }
    
    bool Debug::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Debug [ maxMessageLength ] : " << m_MaxMessageLength;
        NEPTUNE_LOG_CORE(I) << "Debug [ maxLoggedMessages ] : " << m_MaxLoggedMessages;
        NEPTUNE_LOG_CORE(I) << "Debug [ maxGroupStackDepth ] : " << m_MaxGroupStackDepth;

        return true;
    }
    
}

#endif