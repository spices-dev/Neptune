/**
* @file DeviceGroup.cpp.
* @brief The DeviceGroup Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DeviceGroup.h"

namespace Neptune::Vulkan::Extension {

    DeviceGroup::DeviceGroup(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_DEVICE_GROUP_EXTENSION_NAME);
    }

}

#endif