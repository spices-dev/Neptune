/**
* @file Validation.cpp.
* @brief The Validation Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Validation.h"

namespace Neptune::Vulkan::Layer {

    Validation::Validation(ELayerState state)
        : Layer(state)
    {
        NEPTUNE_PROFILE_ZONE
    }

}

#endif