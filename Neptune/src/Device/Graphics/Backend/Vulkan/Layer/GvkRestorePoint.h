/**
* @file GvkRestorePoint.h.
* @brief The GvkRestorePoint Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IGvkRestorePoint = ILayer<class GvkRestorePoint, ELayer::GvkRestorePoint>;

    class GvkRestorePoint : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit GvkRestorePoint(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~GvkRestorePoint() override = default;
    };
}

#endif