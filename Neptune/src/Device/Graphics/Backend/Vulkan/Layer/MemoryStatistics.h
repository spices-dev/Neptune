/**
* @file MemoryStatistics.h.
* @brief The MemoryStatistics Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IMemoryStatistics = ILayer<class MemoryStatistics, ELayer::MemoryStatistics>;

    class MemoryStatistics : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit MemoryStatistics(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~MemoryStatistics() override = default;
    };
}

#endif