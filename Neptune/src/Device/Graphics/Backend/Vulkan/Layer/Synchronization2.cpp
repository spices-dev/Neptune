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
        : Layer("VK_LAYER_KHRONOS_synchronization2", state)
    {
        NEPTUNE_PROFILE_ZONE

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("force_enable", data);
        }
    }

}

#endif