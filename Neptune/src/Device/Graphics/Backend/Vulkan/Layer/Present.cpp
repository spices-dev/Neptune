/**
* @file Present.cpp.
* @brief The Present Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Present.h"

namespace Neptune::Vulkan::Layer {

    Present::Present(ELayerState state)
        : Layer("VK_LAYER_NV_present", state)
    {}

}

#endif