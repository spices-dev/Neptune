/**
* @file KeydMutex.cpp.
* @brief The KeydMutex Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "KeydMutex.h"

namespace Neptune::OpenGL::Capability {

    KeydMutex::KeydMutex(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_EXT_win32_keyed_mutex");
    }

}

#endif