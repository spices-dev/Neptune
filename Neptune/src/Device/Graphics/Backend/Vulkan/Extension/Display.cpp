/**
* @file Display.cpp.
* @brief The Display Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Display.h"

namespace Neptune::Vulkan::Extension {

    Display::Display(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddInstanceExtensions(VK_KHR_SURFACE_EXTENSION_NAME);
        AddInstanceExtensions(VK_KHR_DISPLAY_EXTENSION_NAME);
        AddInstanceExtensions(VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME);
        AddInstanceExtensions(VK_EXT_DIRECT_MODE_DISPLAY_EXTENSION_NAME);
        
        AddDeviceExtensions(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

}

#endif