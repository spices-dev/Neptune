/**
* @file MemoryStatistics.cpp.
* @brief The MemoryStatistics Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Sample.h"

namespace Neptune::Vulkan::Layer {

    Sample::Sample(ELayerState state)
        : Layer("VK_LAYER_NEPTUNE_memory_statistics", state)
    {}

}

#endif