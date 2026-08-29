/**
* @file ScreenShot.h.
* @brief The ScreenShot Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IScreenShot = ILayer<class ScreenShot, ELayer::ScreenShot>;

    class ScreenShot : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit ScreenShot(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~ScreenShot() override = default;
    };
}

#endif