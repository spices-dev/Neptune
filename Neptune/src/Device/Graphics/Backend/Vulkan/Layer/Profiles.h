/**
* @file Profiles.h.
* @brief The Profiles Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IProfiles = ILayer<class Profiles, ELayer::Profiles>;

    class Profiles : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit Profiles(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~Profiles() override = default;
    };
}

#endif