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
        
        glGetIntegerv(GL_MIN_MAP_BUFFER_ALIGNMENT, &m_MinMapAlignment);
    }

}

#endif