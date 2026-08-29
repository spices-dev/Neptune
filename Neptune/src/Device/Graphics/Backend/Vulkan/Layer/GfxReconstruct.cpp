/**
* @file GfxReconstruct.cpp.
* @brief The GfxReconstruct Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GfxReconstruct.h"

namespace Neptune::Vulkan::Layer {

    GfxReconstruct::GfxReconstruct(ELayerState state)
        : Layer(state)
    {
        NEPTUNE_PROFILE_ZONE
    }

}

#endif