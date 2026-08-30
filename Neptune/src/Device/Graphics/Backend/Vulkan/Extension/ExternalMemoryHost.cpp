/**
* @file ExternalMemoryHost.cpp.
* @brief The ExternalMemoryHost Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ExternalMemoryHost.h"

namespace Neptune::Vulkan::Extension {

    ExternalMemoryHost::ExternalMemoryHost(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_EXT_EXTERNAL_MEMORY_HOST_EXTENSION_NAME);
    }

}

#endif