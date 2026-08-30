/**
* @file GfxReconstruct.cpp.
* @brief The GfxReconstruct Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GfxReconstruct.h"

namespace Neptune::Vulkan::Layer {

    GfxReconstruct::GfxReconstruct(ELayerState state)
        : Layer("VK_LAYER_LUNARG_gfxreconstruct", state)
    {
        NEPTUNE_PROFILE_ZONE

        {
            static const char* data            = "F12";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_trigger";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "frames";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_trigger_boundary";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_trigger_frames";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_frames";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_process_name";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "gfxrecon_capture.gfxr";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_file";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_file_timestamp";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_file_flush";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "LZ4";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_compression_type";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "capture_environment";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "page_guard";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "memory_tracking_mode";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "page_guard_copy_on_map";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "page_guard_separate_read";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "page_guard_external_memory";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "page_guard_persistent_memory";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "page_guard_align_buffer_sizes";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "page_guard_unblock_sigsegv";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "info";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_level";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_detailed";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_allow_indents";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_output_to_console";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_break_on_error";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_output_to_os_debug_string";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "vk_gfx_reconstruct.txt";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_file";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_file_flush_after_write";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_file_keep_open";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_file_create_new";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }
    }

}

#endif