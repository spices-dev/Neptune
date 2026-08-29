/**
* @file GfxReconstruct.h.
* @brief The GfxReconstruct Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IGfxReconstruct = ILayer<class GfxReconstruct, ELayer::GfxReconstruct>;

    class GfxReconstruct : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit GfxReconstruct(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~GfxReconstruct() override = default;
    };
}

#endif