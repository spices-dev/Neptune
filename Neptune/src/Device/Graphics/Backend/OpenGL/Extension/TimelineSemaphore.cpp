/**
* @file TimelineSemaphore.cpp.
* @brief The TimelineSemaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TimelineSemaphore.h"

namespace Neptune::OpenGL::Extension {

    TimelineSemaphore::TimelineSemaphore(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddExtensions("GL_NV_timeline_semaphore");
    }

    void TimelineSemaphore::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetIntegerv(GL_MAX_TIMELINE_SEMAPHORE_VALUE_DIFFERENCE_NV, &m_MaxValueDifference);
    }
    
    bool TimelineSemaphore::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "TimelineSemaphore [ maxValueDifference ] : " << m_MaxValueDifference;

        return true;
    }
    
}

#endif