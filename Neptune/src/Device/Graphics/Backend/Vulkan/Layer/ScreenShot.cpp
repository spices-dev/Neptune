/**
* @file ScreenShot.cpp.
* @brief The ScreenShot Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ScreenShot.h"

namespace Neptune::Vulkan::Layer {

    ScreenShot::ScreenShot(ELayerState state)
        : Layer(state)
    {
        NEPTUNE_PROFILE_ZONE
    }

}

#endif