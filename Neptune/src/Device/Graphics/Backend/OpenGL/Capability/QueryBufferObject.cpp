/**
* @file QueryBufferObject.cpp.
* @brief The QueryBufferObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "QueryBufferObject.h"

namespace Neptune::OpenGL::Capability {

    QueryBufferObject::QueryBufferObject(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_query_buffer_object");
    }

}

#endif