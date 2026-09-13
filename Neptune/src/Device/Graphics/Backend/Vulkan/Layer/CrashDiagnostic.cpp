/**
* @file CrashDiagnostic.cpp.
* @brief The CrashDiagnostic Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "CrashDiagnostic.h"

namespace Neptune::Vulkan::Layer {

    CrashDiagnostic::CrashDiagnostic(ELayerState state)
        : Layer("VK_LAYER_LUNARG_crash_diagnostic", state)
    {
        NEPTUNE_PROFILE_ZONE

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("sync_after_commands", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("instrument_all_commands", data);
        }

        {
            static const char* data = "cache/CrashDiagnostic";

            AddLayerSetting("output_path", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("trigger_watchdog_timeout", data);
        }

        {
            static constexpr int64_t data = 30000;

            AddLayerSetting("watchdog_timeout_ms", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("track_semaphores", data);
        }

        {
            static const char* data = "running";

            AddLayerSetting("dump_queue_submits", data);
        }

        {
            static const char* data = "all";

            AddLayerSetting("dump_command_buffers", data);
        }

        {
            static const char* data = "all";

            AddLayerSetting("dump_commands", data);
        }

        {
            static const char* data = "all";

            AddLayerSetting("dump_shaders", data);
        }

        {
            static const char* data = "vk_crash_diagnostic.txt";

            AddLayerSetting("log_file", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("trace_on", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("trace_all_semaphores", data);
        }

        {
            static const char* data = "error";

            AddLayerSetting("message_severity", data);
        }
    }

}

#endif