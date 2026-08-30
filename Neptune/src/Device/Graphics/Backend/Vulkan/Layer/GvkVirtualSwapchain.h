/**
* @file GvkVirtualSwapchain.h.
* @brief The GvkVirtualSwapchain Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IGvkVirtualSwapchain = ILayer<class GvkVirtualSwapchain, ELayer::GvkVirtualSwapchain>;

    class GvkVirtualSwapchain : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit GvkVirtualSwapchain(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~GvkVirtualSwapchain() override = default;
    };
}

#endif