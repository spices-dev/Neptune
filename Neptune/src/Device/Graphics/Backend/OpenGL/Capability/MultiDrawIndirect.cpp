/**
* @file MultiDrawIndirect.cpp.
* @brief The MultiDrawIndirect Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "MultiDrawIndirect.h"

namespace Neptune::OpenGL::Capability {

    MultiDrawIndirect::MultiDrawIndirect(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_multi_draw_indirect");
    }

}

#endif