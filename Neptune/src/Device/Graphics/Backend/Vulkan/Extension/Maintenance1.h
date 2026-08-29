/**
* @file Maintenance1.h.
* @brief The Maintenance1 Class Definitions.
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
        * 
        * @param[in] state EExtensionState.
        */
        explicit Maintenance1(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Maintenance1() override = default;
    };
}

#endif