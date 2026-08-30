/**
* @file ShaderObject.cpp.
* @brief The ShaderObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ShaderObject.h"

namespace Neptune::Vulkan::Layer {

    ShaderObject::ShaderObject(ELayerState state)
        : Layer("VK_LAYER_KHRONOS_shader_object", state)
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

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "disable_pipeline_pre_caching";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }
    }

}

#endif