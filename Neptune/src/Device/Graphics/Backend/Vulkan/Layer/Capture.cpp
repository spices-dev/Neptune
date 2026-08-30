/**
* @file Capture.cpp.
* @brief The Capture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Capture.h"

namespace Neptune::Vulkan::Layer {

    Capture::Capture(ELayerState state)
        : Layer("VK_LAYER_RENDERDOC_Capture", state)
    {}

}

#endif