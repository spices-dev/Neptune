/**
* @file Robustness.cpp.
* @brief The Robustness Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Robustness.h"

namespace Neptune::OpenGL::Capability {

    Robustness::Robustness(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_ARB_robustness");
        
        // TODO
    }

}

#endif