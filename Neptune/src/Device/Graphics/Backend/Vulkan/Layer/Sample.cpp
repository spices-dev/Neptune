/**
* @file Sample.cpp.
* @brief The Sample Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Sample.h"

namespace Neptune::Vulkan::Layer {

    Sample::Sample(ELayerState state)
        : Layer("VK_LAYER_NEPTUNE_sample", state)
    {}

}

#endif