/**
* @file DeviceAddressCommands.h.
* @brief The DeviceAddressCommands Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDeviceAddressCommands = IExtension<class DeviceAddressCommands, EExtension::DeviceAddressCommands>;

    /**
    * @brief Used In:
    * vkCmdDispatchIndirect2KHR
    */
    class DeviceAddressCommands : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit DeviceAddressCommands(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~DeviceAddressCommands() override = default;
    
    };
}

#endif