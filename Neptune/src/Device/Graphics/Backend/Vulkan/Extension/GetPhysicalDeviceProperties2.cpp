/**
* @file GetPhysicalDeviceProperties2.cpp.
* @brief The GetPhysicalDeviceProperties2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GetPhysicalDeviceProperties2.h"

namespace Neptune::Vulkan::Extension {

    GetPhysicalDeviceProperties2::GetPhysicalDeviceProperties2(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddInstanceExtensions(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    }

}

#endif