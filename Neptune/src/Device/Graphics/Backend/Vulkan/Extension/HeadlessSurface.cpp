/**
* @file HeadlessSurface.cpp.
* @brief The HeadlessSurface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "HeadlessSurface.h"

namespace Neptune::Vulkan::Extension {

    HeadlessSurface::HeadlessSurface(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddInstanceExtensions(VK_KHR_SURFACE_EXTENSION_NAME);
        AddInstanceExtensions(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME);
        
        AddDeviceExtensions(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

}

#endif