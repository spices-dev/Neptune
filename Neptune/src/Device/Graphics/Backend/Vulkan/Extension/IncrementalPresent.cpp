/**
* @file IncrementalPresent.cpp.
* @brief The IncrementalPresent Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IncrementalPresent.h"

namespace Neptune::Vulkan::Extension {
    
    IncrementalPresent::IncrementalPresent(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddDeviceExtensions(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_INCREMENTAL_PRESENT_EXTENSION_NAME);
    }
}

#endif