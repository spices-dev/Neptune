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
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("profile_emulation", data);
        }

        {
            static constexpr char data[] = "cache/Profiles";

            AddLayerSetting("profile_dirs", data);
        }

        {
            static constexpr char data[] = "${VP_DEFAULT}";

            AddLayerSetting("profile_name", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("profile_validation", data);
        }

        {
            static constexpr char data[] = "SIMULATE_API_VERSION_BIT,SIMULATE_FEATURES_BIT,SIMULATE_PROPERTIES_BIT,SIMULATE_EXTENSIONS_BIT,SIMULATE_FORMATS_BIT,SIMULATE_VIDEO_CAPABILITIES_BIT,SIMULATE_VIDEO_FORMATS_BIT";

            AddLayerSetting("simulate_capabilities", data);
        }

        {
            static constexpr char data[] = "DEFAULT_FEATURE_VALUES_DEVICE";

            AddLayerSetting("default_feature_values", data);
        }

        {
            static constexpr char data[] = "UNKNOWN_FEATURE_VALUES_UNCHANGED";

            AddLayerSetting("unknown_feature_values", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("emulate_portability", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("constantAlphaColorBlendFactors", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("events", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("imageViewFormatReinterpretation", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("imageViewFormatSwizzle", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("imageView2DOn3DImage", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("multisampleArrayImage", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("mutableComparisonSamplers", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("pointPolygons", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("samplerMipLodBias", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("separateStencilMaskRef", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("shaderSampleRateInterpolationFunctions", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("tessellationIsolines", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("triangleFans", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("vertexAttributeAccessBeyondStride", data);
        }

        {
            static constexpr int64_t data = 4;

            AddLayerSetting("minVertexInputBindingStrideAlignment", data);
        }

        {
            static constexpr char data[] = "";

            AddLayerSetting("exclude_device_extensions", data);
        }

        {
            static constexpr char data[] = "";

            AddLayerSetting("exclude_formats", data);
        }

        {
            static constexpr char data[] = "DEBUG_ACTION_STDOUT_BIT,DEBUG_ACTION_OUTPUT_BIT,DEBUG_ACTION_FILE_BIT,DEBUG_ACTION_BREAKPOINT_BIT";

            AddLayerSetting("debug_actions", data);
        }

        {
            static constexpr char data[] = "vk_profiles.txt";

            AddLayerSetting("debug_filename", data);
        }

        {
            static constexpr VkBool32 data = VK_TRUE;

            AddLayerSetting("debug_file_clear", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("debug_fail_on_error", data);
        }

        {
            static constexpr char data[] = "DEBUG_REPORT_NOTIFICATION_BIT,DEBUG_REPORT_WARNING_BIT,DEBUG_REPORT_ERROR_BIT";

            AddLayerSetting("debug_reports", data);
        }
    }

}

#endif