/**
* @file ShaderViewportLayerArray.cpp.
* @brief The ShaderViewportLayerArray Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShaderViewportLayerArray.h"

namespace Neptune::OpenGL::Capability {

    ShaderViewportLayerArray::ShaderViewportLayerArray(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_shader_viewport_layer_array");
    }

}

#endif