/**
* @file DeviceGeneratedCommands.cpp.
* @brief The DeviceGeneratedCommands Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DeviceGeneratedCommands.h"

namespace Neptune::Vulkan::Extension {

    DeviceGeneratedCommands::DeviceGeneratedCommands(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_EXT_DEVICE_GENERATED_COMMANDS_EXTENSION_NAME);
    }

}

#endif