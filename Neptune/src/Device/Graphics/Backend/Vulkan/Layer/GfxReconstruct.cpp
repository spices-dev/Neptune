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
            static constexpr char data[] = "F12";

            AddLayerSetting("capture_trigger", data);
        }

        {
            static constexpr char data[] = "frames";

            AddLayerSetting("capture_trigger_boundary", data);
        }

        {
            static constexpr char data[] = "";

            AddLayerSetting("capture_trigger_frames", data);
        }

        {
            static constexpr char data[] = "";

            AddLayerSetting("capture_frames", data);
        }

        {
            static constexpr char data[] = "";

            AddLayerSetting("capture_process_name", data);
        }

        {
            static constexpr char data[] = "cache/GfxReconstruct/gfxrecon_capture.gfxr";

            AddLayerSetting("capture_file", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("capture_file_timestamp", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("capture_file_flush", data);
        }

        {
            static constexpr char data[] = "LZ4";

            AddLayerSetting("capture_compression_type", data);
        }

        {
            static constexpr char data[] = "";

            AddLayerSetting("capture_environment", data);
        }

        {
            static constexpr char data[] = "page_guard";

            AddLayerSetting("memory_tracking_mode", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("page_guard_copy_on_map", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("page_guard_separate_read", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("page_guard_external_memory", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("page_guard_persistent_memory", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("page_guard_align_buffer_sizes", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("page_guard_unblock_sigsegv", data);
        }

        {
            static constexpr char data[] = "info";

            AddLayerSetting("log_level", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("log_detailed", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("log_allow_indents", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("log_output_to_console", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("log_break_on_error", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("log_output_to_os_debug_string", data);
        }

        {
            static constexpr char data[] = "cache/GfxReconstruct/vk_gfx_reconstruct.txt";

            AddLayerSetting("log_file", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("log_file_flush_after_write", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("log_file_keep_open", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("log_file_create_new", data);
        }
    }

}

#endif