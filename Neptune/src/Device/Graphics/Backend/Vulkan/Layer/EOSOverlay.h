/**
* @file EOSOverlay.h.
* @brief The EOSOverlay Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IEOSOverlay = ILayer<class EOSOverlay, ELayer::EOSOverlay>;

    class EOSOverlay : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit EOSOverlay(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~EOSOverlay() override = default;
    };
}

#endif