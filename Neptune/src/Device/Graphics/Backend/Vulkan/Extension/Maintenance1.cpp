/**
* @file Maintenance1.cpp.
* @brief The Maintenance1 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Maintenance1.h"

namespace Neptune::Vulkan::Extension {
    
    Maintenance1::Maintenance1(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        AddDeviceExtensions(VK_KHR_MAINTENANCE_1_EXTENSION_NAME);
    }
    
}

#endif