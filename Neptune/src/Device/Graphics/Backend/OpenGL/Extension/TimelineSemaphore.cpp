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

        if constexpr (IsCoreExtension<decltype(*this)>) return;
        
        AddExtensions("GL_NV_timeline_semaphore");
        
        glGetIntegerv(GL_MAX_TIMELINE_SEMAPHORE_VALUE_DIFFERENCE_NV, &m_MaxValueDifference);
    }

}

#endif