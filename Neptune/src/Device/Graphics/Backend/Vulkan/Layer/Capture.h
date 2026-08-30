/**
* @file Capture.h.
* @brief The Capture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using ICapture = ILayer<class Capture, ELayer::Capture>;

    class Capture : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit Capture(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~Capture() override = default;
    };
}

#endif