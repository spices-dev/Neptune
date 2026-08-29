/**
* @file HDR.cpp.
* @brief The HDR Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "HDR.h"

namespace Neptune::Vulkan::Extension {
    
    HDR::HDR(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        AddInstanceExtensions(VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME);
        
        AddDeviceExtensions(VK_EXT_HDR_METADATA_EXTENSION_NAME);
    }
    
}

#endif