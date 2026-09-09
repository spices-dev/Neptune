/**
* @file Semaphore.cpp.
* @brief The Semaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Semaphore.h"

namespace Neptune::OpenGL::Capability {

    Semaphore::Semaphore(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_EXT_semaphore");
#ifdef NP_PLATFORM_WINDOWS
        AddExtensions("GL_EXT_semaphore_wn32");
#else
        AddExtensions("GL_EXT_semaphore_fd");
#endif
        
    }

}

#endif