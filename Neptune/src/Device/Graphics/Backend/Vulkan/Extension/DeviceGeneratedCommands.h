/**
* @file DeviceGeneratedCommands.h.
* @brief The DeviceGeneratedCommands Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDeviceGeneratedCommands = IExtension<class DeviceGeneratedCommands, EExtension::DeviceGeneratedCommands>;

    /**
    * @brief Used In:
    * VK_LAYER_KHRONOS_validation gpu_dump_device_generated_commands
    */
    class DeviceGeneratedCommands : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit DeviceGeneratedCommands(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~DeviceGeneratedCommands() override = default;
    };
}

#endif