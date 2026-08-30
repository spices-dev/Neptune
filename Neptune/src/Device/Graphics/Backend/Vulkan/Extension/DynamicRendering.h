/**
* @file DynamicRendering.h.
* @brief The DynamicRendering Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDynamicRendering = IExtension<class DynamicRendering, EExtension::DynamicRendering>;

    /**
    * @brief Used In:
    * Seperate Pipeline State
    * VK_LAYER_LUNARG_crash_diagnostic sync_after_commands
    */
    class DynamicRendering : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit DynamicRendering(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~DynamicRendering() override = default;
    };
}

#endif