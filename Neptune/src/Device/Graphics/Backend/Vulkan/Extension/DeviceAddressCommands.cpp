/**
* @file DeviceAddressCommands.cpp.
* @brief The DeviceAddressCommands Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DeviceAddressCommands.h"

namespace Neptune::Vulkan::Extension {
    
    DeviceAddressCommands::DeviceAddressCommands(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_DEVICE_ADDRESS_COMMANDS_EXTENSION_NAME);
    }
}

#endif