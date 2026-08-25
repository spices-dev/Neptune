/**
* @file Maintenance1.h.
* @brief The Maintenance1 Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IMaintenance1 = IExtension<class Maintenance1, EExtension::Maintenance1>;
    
    class Maintenance1 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Maintenance1();
        
        /**
        * @brief Destructor Function.
        */
        ~Maintenance1() override = default;
    };
}

#endif