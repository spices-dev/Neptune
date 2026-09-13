/**
* @file KeydMutex.cpp.
* @brief The KeydMutex Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "KeydMutex.h"

namespace Neptune::OpenGL::Extension {

    KeydMutex::KeydMutex(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddExtensions("GL_EXT_win32_keyed_mutex");
    }

}

#endif