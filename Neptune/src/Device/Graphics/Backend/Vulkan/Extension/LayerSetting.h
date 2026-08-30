/**
* @file LayerSetting.h.
* @brief The LayerSetting Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using ILayerSetting = IExtension<class LayerSetting, EExtension::LayerSetting>;

    class LayerSetting : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit LayerSetting(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~LayerSetting() override = default;
    };
}

#endif