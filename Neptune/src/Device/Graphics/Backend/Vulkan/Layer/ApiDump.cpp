/**
* @file ApiDump.cpp.
* @brief The ApiDump Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ApiDump.h"

namespace Neptune::Vulkan::Layer {

    ApiDump::ApiDump(ELayerState state)
        : Layer("VK_LAYER_LUNARG_api_dump", state)
    {
        NEPTUNE_PROFILE_ZONE

        {
            static const char* data = "0-0";

            AddLayerSetting("output_range", data);
        }

        {
            static const char* data = "text";

            AddLayerSetting("output_format", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("pre_dump", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("file", data);
        }

        {
            static const char* data = "cache/vk_api_dump.txt";

            AddLayerSetting("log_filename", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("flush", data);
        }

        {
            static constexpr int64_t data = 32;

            AddLayerSetting("name_size", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("show_types", data);
        }

        {
            static constexpr int64_t data = 0;

            AddLayerSetting("type_size", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("timestamp", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("show_shader", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("detailed", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("no_addr", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("use_spaces", data);
        }

        {
            static constexpr int64_t data = 4;

            AddLayerSetting("indent_size", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("show_thread_and_frame", data);
        }
    }

}

#endif