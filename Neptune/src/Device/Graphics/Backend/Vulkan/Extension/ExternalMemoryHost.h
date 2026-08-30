/**
* @file ExternalMemoryHost.h.
* @brief The ExternalMemoryHost Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IExternalMemoryHost = IExtension<class ExternalMemoryHost, EExtension::ExternalMemoryHost>;

    /**
    * @brief Used In:
    * VK_LAYER_LUNARG_gfxreconstruct page_guard_external_memory
    */
    class ExternalMemoryHost : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ExternalMemoryHost(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ExternalMemoryHost() override = default;
    };
}

#endif