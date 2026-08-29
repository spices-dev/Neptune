/**
* @file Profiles.cpp.
* @brief The Profiles Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Profiles.h"

namespace Neptune::Vulkan::Layer {

    Profiles::Profiles(ELayerState state)
        : Layer(state)
    {
        NEPTUNE_PROFILE_ZONE
    }

}

#endif