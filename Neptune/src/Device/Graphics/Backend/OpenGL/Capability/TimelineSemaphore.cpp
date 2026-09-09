/**
* @file TimelineSemaphore.cpp.
* @brief The TimelineSemaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TimelineSemaphore.h"

namespace Neptune::OpenGL::Capability {

    TimelineSemaphore::TimelineSemaphore(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_NV_timeline_semaphore");
        
        glGetIntegerv(GL_MAX_TIMELINE_SEMAPHORE_VALUE_DIFFERENCE_NV, &m_MaxValueDifference);
    }

}

#endif