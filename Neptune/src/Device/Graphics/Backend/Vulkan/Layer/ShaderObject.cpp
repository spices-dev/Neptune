/**
* @file ShaderObject.cpp.
* @brief The ShaderObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ShaderObject.h"

namespace Neptune::Vulkan::Layer {

    ShaderObject::ShaderObject(ELayerState state)
        : Layer(state)
    {
        NEPTUNE_PROFILE_ZONE
    }

}

#endif