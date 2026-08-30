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
        : Layer("VK_LAYER_KHRONOS_profiles", state)
    {
        NEPTUNE_PROFILE_ZONE

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "profile_emulation";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data           = "cached/Profiles";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "profile_dirs";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "${VP_DEFAULT}";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "profile_name";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "profile_validation";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "SIMULATE_API_VERSION_BIT,SIMULATE_FEATURES_BIT,SIMULATE_PROPERTIES_BIT,SIMULATE_EXTENSIONS_BIT,SIMULATE_FORMATS_BIT,SIMULATE_VIDEO_CAPABILITIES_BIT,SIMULATE_VIDEO_FORMATS_BIT";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "simulate_capabilities";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "DEFAULT_FEATURE_VALUES_DEVICE";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "default_feature_values";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "UNKNOWN_FEATURE_VALUES_UNCHANGED";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "unknown_feature_values";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "emulate_portability";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "constantAlphaColorBlendFactors";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "events";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "imageViewFormatReinterpretation";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "imageViewFormatSwizzle";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "imageView2DOn3DImage";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "multisampleArrayImage";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "mutableComparisonSamplers";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "pointPolygons";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "samplerMipLodBias";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "separateStencilMaskRef";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "shaderSampleRateInterpolationFunctions";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "tessellationIsolines";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "triangleFans";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "vertexAttributeAccessBeyondStride";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const int64_t data          = 4;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "minVertexInputBindingStrideAlignment";
            settings.type                      = VK_LAYER_SETTING_TYPE_INT64_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "exclude_device_extensions";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "exclude_formats";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "DEBUG_ACTION_STDOUT_BIT,DEBUG_ACTION_OUTPUT_BIT,DEBUG_ACTION_FILE_BIT,DEBUG_ACTION_BREAKPOINT_BIT";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "debug_actions";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "vk_profiles.txt";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "debug_filename";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "debug_file_clear";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "debug_fail_on_error";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "DEBUG_REPORT_NOTIFICATION_BIT,DEBUG_REPORT_WARNING_BIT,DEBUG_REPORT_ERROR_BIT";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "debug_reports";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }
    }

}

#endif