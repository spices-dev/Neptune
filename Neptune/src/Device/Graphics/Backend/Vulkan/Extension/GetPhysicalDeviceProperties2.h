/**
* @file GetPhysicalDeviceProperties2.h.
* @brief The GetPhysicalDeviceProperties2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IGetPhysicalDeviceProperties2 = IExtension<class GetPhysicalDeviceProperties2, EExtension::ExternalMemoryHost>;

    class GetPhysicalDeviceProperties2 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit GetPhysicalDeviceProperties2(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~GetPhysicalDeviceProperties2() override = default;
    };
}

#endif