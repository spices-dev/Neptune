/**
* @file Synchronization2.h.
* @brief The Synchronization2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using ISynchronization2 = ILayer<class Synchronization2, ELayer::Synchronization2>;

    class Synchronization2 : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit Synchronization2(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~Synchronization2() override = default;
    };
}

#endif