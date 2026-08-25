/**
* @file YCrBrConversion.h.
* @brief The YCrBrConversion Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IYCrBrConversion = IExtension<class YCrBrConversion, EExtension::YCrBrConversion>;
    
    class YCrBrConversion : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        YCrBrConversion();
        
        /**
        * @brief Destructor Function.
        */
        ~YCrBrConversion() override = default;
    };
}

#endif