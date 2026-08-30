/**
* @file Optimus.cpp.
* @brief The Optimus Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Optimus.h"

namespace Neptune::Vulkan::Layer {

    Optimus::Optimus(ELayerState state)
        : Layer("VK_LAYER_NV_optimus", state)
    {}

}

#endif