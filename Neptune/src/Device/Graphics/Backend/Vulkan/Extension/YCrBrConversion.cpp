/**
* @file YCrBrConversion.cpp.
* @brief The YCrBrConversion Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "YCrBrConversion.h"

namespace Neptune::Vulkan::Extension {
    
    YCrBrConversion::YCrBrConversion()
    {
        NEPTUNE_PROFILE_ZONE
        
        AddDeviceExtensions(VK_KHR_SAMPLER_YCBCR_CONVERSION_EXTENSION_NAME);
    }
    
}

#endif