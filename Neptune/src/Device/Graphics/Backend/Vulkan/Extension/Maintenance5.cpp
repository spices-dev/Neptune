/**
* @file Maintenance5.cpp.
* @brief The Maintenance5 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Maintenance5.h"

namespace Neptune::Vulkan::Extension {
    
    Maintenance5::Maintenance5(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_MAINTENANCE_5_EXTENSION_NAME);
    }
    
}

#endif