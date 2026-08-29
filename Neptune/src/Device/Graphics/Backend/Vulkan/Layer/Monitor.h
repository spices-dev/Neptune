/**
* @file Monitor.h.
* @brief The Monitor Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IMonitor = ILayer<class Monitor, ELayer::Monitor>;

    class Monitor : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit Monitor(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~Monitor() override = default;
    };
}

#endif