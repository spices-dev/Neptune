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
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("validate_core", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("check_shaders", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("check_shaders_caching", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("validate_sync", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("syncval_submit_time_validation", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("syncval_shader_accesses_heuristic", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("syncval_message_extra_properties", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("stateless_param", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("object_lifetime", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("thread_safety", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("unique_handles", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("legacy_detection", data);
        }

        {
            static const char* data = "ALWAYS";

            AddLayerSetting("legacy_detection_mode", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("validate_best_practices", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("validate_best_practices_arm", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("validate_best_practices_amd", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("validate_best_practices_img", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("validate_best_practices_nvidia", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("gpuav_enable", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("gpuav_safe_mode", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("gpuav_force_on_robustness", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("gpuav_shader_instrumentation", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("gpuav_ray_tracing_buffers_consistency", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("gpuav_select_instrumented_shaders", data);
        }

        {
            static const char* data = "";

            AddLayerSetting("gpuav_shaders_to_instrument", data);
        }

        {
            static const char* data = "cache/CdlDump";

            AddLayerSetting("gpuav_cdl_dump_path", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("gpu_dump_descriptors", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("gpu_dump_copy_memory_indirect", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("gpu_dump_device_generated_commands", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("gpu_dump_to_stdout", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("descriptor_hashing", data);
        }

        {
            static constexpr int64_t data = 65536;

            AddLayerSetting("descriptor_hashing_total_descriptors", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("printf_enable", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("printf_to_stdout", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("printf_verbose", data);
        }

        {
            static constexpr int64_t data = 1024;

            AddLayerSetting("printf_buffer_size", data);
        }

        {
            static const char* data = "VK_DBG_LAYER_ACTION_LOG_MSG,VK_DBG_LAYER_ACTION_DEBUG_OUTPUT";

            AddLayerSetting("debug_action", data);
        }

        {
            static const char* data = "stdout";

            AddLayerSetting("log_filename", data);
        }

        {
            static const char* data = "error,warn";

            AddLayerSetting("report_flags", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("enable_message_limit", data);
        }

        {
            static constexpr int64_t data = 10;

            AddLayerSetting("duplicate_message_limit", data);
        }

        {
            static const char* data = "";

            AddLayerSetting("message_id_filter", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("message_format_json", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("message_format_display_application_name", data);
        }
    }

}

#endif