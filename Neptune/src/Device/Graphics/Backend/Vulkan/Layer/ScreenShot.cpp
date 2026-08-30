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
        : Layer("VK_LAYER_LUNARG_screenshot", state)
    {
        NEPTUNE_PROFILE_ZONE

        {
            static const char* data            = "";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "frames";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "cache/ScreenShot";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "dir";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "USE_SWAPCHAIN_COLORSPACE";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "format";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }
    }

}

#endif