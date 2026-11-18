/**
* @file Display.h.
* @brief The Display Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDisplay = IExtension<class Display, EExtension::Display>;
    
    class Display : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit Display(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~Display() override = default;
    };
}

#endif