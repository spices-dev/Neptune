/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SwapChain.h"

namespace Neptune::Vulkan::Extension {
    
    SwapChain::SwapChain(const std::vector<const char*>& windowExtensions)
    {
        NEPTUNE_PROFILE_ZONE
        
        for (const auto& extension : windowExtensions)
        {
            AddInstanceExtensions(extension);
        }
        
        AddDeviceExtensions(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }
    
}

#endif