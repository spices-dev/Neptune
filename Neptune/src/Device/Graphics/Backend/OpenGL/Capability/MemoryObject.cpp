/**
* @file MemoryObject.cpp.
* @brief The MemoryObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "MemoryObject.h"

namespace Neptune::OpenGL::Capability {

    MemoryObject::MemoryObject(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

#ifdef NP_PLATFORM_WINDOWS
        AddExtensions("GL_EXT_memory_object_win32");
#else
        AddExtensions("GL_EXT_memory_object_fd");
#endif
        
    }

}

#endif