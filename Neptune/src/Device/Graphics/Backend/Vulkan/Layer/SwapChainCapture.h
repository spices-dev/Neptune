/**
* @file SwapChainCapture.h.
* @brief The SwapChainCapture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using ISwapChainCapture = ILayer<class SwapChainCapture, ELayer::SwapChainCapture>;

    class SwapChainCapture : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit SwapChainCapture(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~SwapChainCapture() override = default;
    };
}

#endif