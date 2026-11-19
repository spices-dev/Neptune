/**
* @file HeadlessSurface.h.
* @brief The HeadlessSurface Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IHeadlessSurface = IExtension<class HeadlessSurface, EExtension::HeadlessSurface>;
    
    class HeadlessSurface : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit HeadlessSurface(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~HeadlessSurface() override = default;
    };
}

#endif