/**
* @file Validation.h.
* @brief The Validation Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IValidation = ILayer<class Validation, ELayer::Validation>;

    class Validation : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit Validation(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~Validation() override = default;
    };
}

#endif