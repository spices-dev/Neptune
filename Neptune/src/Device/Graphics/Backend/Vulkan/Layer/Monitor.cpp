/**
* @file Monitor.cpp.
* @brief The Monitor Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Monitor.h"

namespace Neptune::Vulkan::Layer {

    Monitor::Monitor(ELayerState state)
        : Layer("VK_LAYER_LUNARG_monitor", state)
    {
        NEPTUNE_PROFILE_ZONE
    }

}

#endif