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
            static constexpr char data[] = "";

            AddLayerSetting("frames", data);
        }

        {
            static constexpr char data[] = "cache/ScreenShot";

            AddLayerSetting("dir", data);
        }

        {
            static constexpr char data[] = "USE_SWAPCHAIN_COLORSPACE";

            AddLayerSetting("format", data);
        }
    }

}

#endif