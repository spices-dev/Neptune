/**
* @file DeviceFault.h.
* @brief The DeviceFault Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDeviceFault = IExtension<class DeviceFault, EExtension::DeviceFault>;
    
    class DeviceFault : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        DeviceFault();
        
        /**
        * @brief Destructor Function.
        */
        ~DeviceFault() override = default;
    };
}

#endif