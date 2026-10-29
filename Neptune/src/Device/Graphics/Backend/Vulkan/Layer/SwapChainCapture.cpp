/**
* @file SwapChainCapture.cpp.
* @brief The SwapChainCapture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SwapChainCapture.h"

namespace Neptune::Vulkan::Layer {

    SwapChainCapture::SwapChainCapture(ELayerState state)
        : Layer("VK_LAYER_NEPTUNE_swapchain_capture", state)
    {}

}

#endif