/**
* @file ViewportLayerArray.cpp.
* @brief The ViewportLayerArray Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ViewportLayerArray.h"

namespace Neptune::OpenGL::Capability {

    ViewportLayerArray::ViewportLayerArray(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_ARB_viewport_layer_array");
    }

}

#endif