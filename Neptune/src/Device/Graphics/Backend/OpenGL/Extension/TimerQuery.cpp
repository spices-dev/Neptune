/**
* @file TimerQuery.cpp.
* @brief The TimerQuery Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TimerQuery.h"

namespace Neptune::OpenGL::Extension {

    TimerQuery::TimerQuery(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_timer_query");
    }
    
    void TimerQuery::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetQueryiv(GL_TIMESTAMP, GL_QUERY_COUNTER_BITS, &m_TimestampBits);
        glGetQueryiv(GL_TIME_ELAPSED, GL_QUERY_COUNTER_BITS, &m_TimeElapsedBits);
    }
    
    bool TimerQuery::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "TimerQuery [ timestampBits ] : " << m_TimestampBits;
        NEPTUNE_LOG_CORE(I) << "TimerQuery [ timeElapsedBits ] : " << m_TimeElapsedBits;

        return true;
    }

}

#endif