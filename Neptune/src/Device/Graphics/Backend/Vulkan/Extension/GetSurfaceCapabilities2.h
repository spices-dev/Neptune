/**
* @file GetSurfaceCapabilities2.h.
* @brief The GetSurfaceCapabilities2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IGetSurfaceCapabilities2 = IExtension<class GetSurfaceCapabilities2, EExtension::GetSurfaceCapabilities2>;

    class GetSurfaceCapabilities2 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit GetSurfaceCapabilities2(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~GetSurfaceCapabilities2() override = default;
    };
}

#endif