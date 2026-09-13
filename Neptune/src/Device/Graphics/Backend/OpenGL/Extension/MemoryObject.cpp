/**
* @file MemoryObject.cpp.
* @brief The MemoryObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "MemoryObject.h"

namespace Neptune::OpenGL::Extension {

    MemoryObject::MemoryObject(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

#ifdef NP_PLATFORM_WINDOWS
        AddExtensions("GL_EXT_memory_object_win32");
#else
        AddExtensions("GL_EXT_memory_object_fd");
#endif
        
    }

}

#endif