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
        : Layer("VK_LAYER_KHRONOS_validation", state)
    {
        NEPTUNE_PROFILE_ZONE

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "validate_core";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "check_shaders";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "check_shaders_caching";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "validate_sync";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "syncval_submit_time_validation";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "syncval_shader_accesses_heuristic";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "syncval_message_extra_properties";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "stateless_param";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "object_lifetime";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "thread_safety";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "unique_handles";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "legacy_detection";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "ALWAYS";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "legacy_detection_mode";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "validate_best_practices";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "validate_best_practices_arm";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "validate_best_practices_amd";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "validate_best_practices_img";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "validate_best_practices_nvidia";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpuav_enable";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpuav_safe_mode";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpuav_force_on_robustness";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpuav_shader_instrumentation";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpuav_ray_tracing_buffers_consistency";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpuav_select_instrumented_shaders";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpuav_shaders_to_instrument";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "cache/CdlDump";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpuav_cdl_dump_path";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpu_dump_descriptors";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpu_dump_copy_memory_indirect";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpu_dump_device_generated_commands";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "gpu_dump_to_stdout";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "descriptor_hashing";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const int64_t data          = 65536;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "descriptor_hashing_total_descriptors ";
            settings.type                      = VK_LAYER_SETTING_TYPE_INT64_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "printf_enable";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "printf_to_stdout";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "printf_verbose";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const int64_t data          = 1024;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "printf_buffer_size";
            settings.type                      = VK_LAYER_SETTING_TYPE_INT64_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "VK_DBG_LAYER_ACTION_LOG_MSG,VK_DBG_LAYER_ACTION_DEBUG_OUTPUT";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "debug_action";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "stdout";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "log_filename";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "error,warn";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "report_flags";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_TRUE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "enable_message_limit";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const int64_t data          = 10;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "duplicate_message_limit";
            settings.type                      = VK_LAYER_SETTING_TYPE_INT64_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const char* data            = "";

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "message_id_filter";
            settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "message_format_json";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }

        {
            static const VkBool32 data         = VK_FALSE;

            VkLayerSettingEXT                    settings {};
            settings.pLayerName                = GetInstanceLayer().c_str();
            settings.pSettingName              = "message_format_display_application_name";
            settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
            settings.valueCount                = 1;
            settings.pValues                   = &data;

            AddLayerSetting(settings);
        }
    }

}

#endif