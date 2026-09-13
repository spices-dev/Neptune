/**
* @file DirectStateAccess.cpp.
* @brief The DirectStateAccess Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "DirectStateAccess.h"

namespace Neptune::OpenGL::Extension {

    DirectStateAccess::DirectStateAccess(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_direct_state_access");
    }

}

#endif