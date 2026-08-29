/**
* @file ApiDump.cpp.
* @brief The ApiDump Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ApiDump.h"

namespace Neptune::Vulkan::Layer {

    ApiDump::ApiDump(ELayerState state)
        : Layer(state)
    {
        NEPTUNE_PROFILE_ZONE
    }

}

#endif