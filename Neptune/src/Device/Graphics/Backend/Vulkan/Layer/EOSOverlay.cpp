/**
* @file EOSOverlay.cpp.
* @brief The EOSOverlay Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "EOSOverlay.h"

namespace Neptune::Vulkan::Layer {

    EOSOverlay::EOSOverlay(ELayerState state)
        : Layer("VK_LAYER_EOS_Overlay", state)
    {}

}

#endif