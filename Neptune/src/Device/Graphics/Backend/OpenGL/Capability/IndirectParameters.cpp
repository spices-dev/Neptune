/**
* @file IndirectParameters.cpp.
* @brief The IndirectParameters Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "IndirectParameters.h"

namespace Neptune::OpenGL::Capability {

    IndirectParameters::IndirectParameters(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_indirect_parameters");
    }

}

#endif