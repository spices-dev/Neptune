/**
* @file GetSurfaceCapabilities2.cpp.
* @brief The GetSurfaceCapabilities2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GetSurfaceCapabilities2.h"

namespace Neptune::Vulkan::Extension {

    GetSurfaceCapabilities2::GetSurfaceCapabilities2(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddInstanceExtensions(VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME);
    }

}

#endif