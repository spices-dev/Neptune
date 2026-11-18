/**
* @file FullScreen.cpp.
* @brief The FullScreen Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "FullScreen.h"

namespace Neptune::Vulkan::Extension {

    FullScreen::FullScreen(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddDeviceExtensions(VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME);
    }

}

#endif