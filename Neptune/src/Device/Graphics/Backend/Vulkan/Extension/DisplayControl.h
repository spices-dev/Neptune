/**
* @file DisplayControl.h.
* @brief The DisplayControl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDisplayControl = IExtension<class DisplayControl, EExtension::DisplayControl>;
    
    class DisplayControl : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit DisplayControl(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~DisplayControl() override = default;
    };
}

#endif