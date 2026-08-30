/**
* @file NgfxCapture.h.
* @brief The NgfxCapture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using INgfxCapture = ILayer<class NgfxCapture, ELayer::NgfxCapture>;

    class NgfxCapture : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit NgfxCapture(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~NgfxCapture() override = default;
    };
}

#endif