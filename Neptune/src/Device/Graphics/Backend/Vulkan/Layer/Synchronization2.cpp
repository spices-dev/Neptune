/**
* @file Synchronization2.cpp.
* @brief The Synchronization2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Synchronization2.h"

namespace Neptune::Vulkan::Layer {

    Synchronization2::Synchronization2(ELayerState state)
        : Layer(state)
    {
        NEPTUNE_PROFILE_ZONE
    }

}

#endif