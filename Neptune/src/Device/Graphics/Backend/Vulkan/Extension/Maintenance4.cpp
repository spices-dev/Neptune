/**
* @file Maintenance4.cpp.
* @brief The Maintenance4 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Maintenance4.h"

namespace Neptune::Vulkan::Extension {
    
    Maintenance4::Maintenance4(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_MAINTENANCE_4_EXTENSION_NAME);
    }
    
}

#endif