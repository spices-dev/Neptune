/**
* @file Present.h.
* @brief The Present Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IPresent = ILayer<class Present, ELayer::Present>;

    class Present : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit Present(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~Present() override = default;
    };
}

#endif