/**
* @file Nomad.h.
* @brief The Nomad Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using INomad = ILayer<class Nomad, ELayer::Nomad>;

    class Nomad : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit Nomad(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~Nomad() override = default;
    };
}

#endif