/**
* @file Optimus.h.
* @brief The Optimus Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IOptimus = ILayer<class Optimus, ELayer::Optimus>;

    class Optimus : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit Optimus(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~Optimus() override = default;
    };
}

#endif