/**
* @file DeviceFault.cpp.
* @brief The DeviceFault Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DeviceFault.h"

namespace Neptune::Vulkan::Extension {
    
    DeviceFault::DeviceFault()
    {
        NEPTUNE_PROFILE_ZONE
        
        AddDeviceExtensions(VK_EXT_DEVICE_FAULT_EXTENSION_NAME);
    }
    
}

#endif