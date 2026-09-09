/**
* @file InvalidateSubdata.cpp.
* @brief The InvalidateSubdata Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "InvalidateSubdata.h"

namespace Neptune::OpenGL::Capability {

    InvalidateSubdata::InvalidateSubdata(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_ARB_invalidate_subdata");
    }

}

#endif