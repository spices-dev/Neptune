/**
* @file DirectStateAccess.cpp.
* @brief The DirectStateAccess Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "DirectStateAccess.h"

namespace Neptune::OpenGL::Capability {

    DirectStateAccess::DirectStateAccess(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_direct_state_access");
    }

}

#endif