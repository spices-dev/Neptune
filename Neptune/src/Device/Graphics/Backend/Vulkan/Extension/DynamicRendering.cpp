/**
* @file DynamicRendering.cpp.
* @brief The DynamicRendering Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DynamicRendering.h"

namespace Neptune::Vulkan::Extension {

    DynamicRendering::DynamicRendering(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddDeviceExtensions(VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME);
    }

}

#endif