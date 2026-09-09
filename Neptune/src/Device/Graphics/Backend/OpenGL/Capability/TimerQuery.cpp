/**
* @file TimerQuery.cpp.
* @brief The TimerQuery Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TimerQuery.h"

namespace Neptune::OpenGL::Capability {

    TimerQuery::TimerQuery(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        //if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_timer_query");
        
        glGetQueryiv(GL_TIMESTAMP, GL_QUERY_COUNTER_BITS, &m_TimestampBits);
        glGetQueryiv(GL_TIME_ELAPSED, GL_QUERY_COUNTER_BITS, &m_TimeElapsedBits);
    }

}

#endif