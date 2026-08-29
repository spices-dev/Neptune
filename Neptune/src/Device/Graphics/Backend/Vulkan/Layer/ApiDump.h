/**
* @file ApiDump.h.
* @brief The ApiDump Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IApiDump = ILayer<class ApiDump, ELayer::ApiDump>;

    class ApiDump : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit ApiDump(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~ApiDump() override = default;
    };
}

#endif