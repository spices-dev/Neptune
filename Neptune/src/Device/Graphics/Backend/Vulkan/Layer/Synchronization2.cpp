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
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "force_enable";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }
    }

}

#endif