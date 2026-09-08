/**
* @file BufferStorage.cpp.
* @brief The BufferStorage Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "BufferStorage.h"

namespace Neptune::OpenGL::Capability {

    BufferStorage::BufferStorage(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_buffer_storage");
        
        glGetIntegerv(GL_MIN_MAP_BUFFER_ALIGNMENT, &m_MinMapAlignment);
    }

}

#endif