/**
* @file BufferStorage.cpp.
* @brief The BufferStorage Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "BufferStorage.h"

namespace Neptune::OpenGL::Extension {

    BufferStorage::BufferStorage(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_buffer_storage");
    }

    void BufferStorage::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetIntegerv(GL_MIN_MAP_BUFFER_ALIGNMENT, &m_MinMapAlignment);
    }
    
    bool BufferStorage::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "BufferStorage [ minMapAlignment ] : " << m_MinMapAlignment;

        return true;
    }
}

#endif