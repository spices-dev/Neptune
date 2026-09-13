/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SwapChain.h"

namespace Neptune::Vulkan::Extension {
    
    SwapChain::SwapChain(EExtensionState state, const std::vector<const char*>& windowExtensions)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        for (const auto& extension : windowExtensions)
        {
            AddInstanceExtensions(extension);
        }
        
        AddDeviceExtensions(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }
    
}

#endif