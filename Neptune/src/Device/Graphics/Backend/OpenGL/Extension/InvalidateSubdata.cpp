/**
* @file InvalidateSubdata.cpp.
* @brief The InvalidateSubdata Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "InvalidateSubdata.h"

namespace Neptune::OpenGL::Extension {

    InvalidateSubdata::InvalidateSubdata(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddExtensions("GL_ARB_invalidate_subdata");
    }

}

#endif