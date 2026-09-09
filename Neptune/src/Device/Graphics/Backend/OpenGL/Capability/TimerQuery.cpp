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

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        // New
        AddExtensions("GL_ARB_timer_query");
        
        // TODO
    }

}

#endif