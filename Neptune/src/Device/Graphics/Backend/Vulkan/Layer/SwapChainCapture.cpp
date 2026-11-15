/**
* @file SwapChainCapture.cpp.
* @brief The SwapChainCapture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SwapChainCapture.h"

namespace Neptune::Vulkan::Layer {

    SwapChainCapture::SwapChainCapture(ELayerState state)
        : Layer("VK_LAYER_NEPTUNE_swapchain_capture", state)
    {
        NEPTUNE_PROFILE_ZONE
        
        {
            static const char* data = "cache/swapchain_capture";

            AddLayerSetting("save_path", data);
        }
        
        {
            static constexpr int64_t data = 60;

            AddLayerSetting("capture_every_n_frames", data);
        }
        
        {
            static constexpr int64_t data = 0;

            AddLayerSetting("max_captures", data);
        }
    }

}

#endif