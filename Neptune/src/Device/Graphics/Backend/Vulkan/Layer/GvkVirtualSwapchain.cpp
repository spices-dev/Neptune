/**
* @file GvkVirtualSwapchain.cpp.
* @brief The GvkVirtualSwapchain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GvkVirtualSwapchain.h"

namespace Neptune::Vulkan::Layer {

    GvkVirtualSwapchain::GvkVirtualSwapchain(ELayerState state)
        : Layer("VK_LAYER_INTEL_gvk_virtual_swapchain", state)
    {}

}

#endif