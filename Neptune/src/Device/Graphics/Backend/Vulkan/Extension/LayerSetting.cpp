/**
* @file HDR.cpp.
* @brief The HDR Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "LayerSetting.h"

namespace Neptune::Vulkan::Extension {

    LayerSetting::LayerSetting(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddInstanceExtensions(VK_EXT_LAYER_SETTINGS_EXTENSION_NAME);
    }

}

#endif