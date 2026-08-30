/**
* @file GvkStateTracker.h.
* @brief The GvkStateTracker Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IGvkStateTracker = ILayer<class GvkStateTracker, ELayer::GvkStateTracker>;

    class GvkStateTracker : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit GvkStateTracker(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~GvkStateTracker() override = default;
    };
}

#endif