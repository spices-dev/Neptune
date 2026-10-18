/**
* @file DeviceGroup.h.
* @brief The DeviceGroup Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDeviceGroup = IExtension<class DeviceGroup, EExtension::DeviceGroup>;
    
    class DeviceGroup : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = VK_MAKE_VERSION(1, 1, 0);
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit DeviceGroup(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~DeviceGroup() override = default;
    };
}

#endif