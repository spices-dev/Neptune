/**
* @file GPUTrace.h.
* @brief The GPUTrace Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IGPUTrace = ILayer<class GPUTrace, ELayer::GPUTrace>;

    class GPUTrace : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit GPUTrace(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~GPUTrace() override = default;
    };
}

#endif