/**
* @file Sample.h.
* @brief The Sample Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using ISample = ILayer<class Sample, ELayer::SwapChainCapture>;

    class Sample : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit Sample(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~Sample() override = default;
    };
}

#endif