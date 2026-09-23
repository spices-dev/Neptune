/**
* @file Maintenance5.h.
* @brief The Maintenance5 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IMaintenance5 = IExtension<class Maintenance5, EExtension::Maintenance5>;
    
    class Maintenance5 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Maintenance5(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Maintenance5() override = default;
    };
}

#endif