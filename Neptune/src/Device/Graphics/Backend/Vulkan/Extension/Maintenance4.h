/**
* @file Maintenance4.h.
* @brief The Maintenance4 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IMaintenance4 = IExtension<class Maintenance4, EExtension::Maintenance4>;
    
    class Maintenance4 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Maintenance4(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Maintenance4() override = default;
    };
}

#endif