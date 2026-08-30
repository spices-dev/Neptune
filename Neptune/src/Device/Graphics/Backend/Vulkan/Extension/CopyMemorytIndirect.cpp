/**
* @file CopyMemorytIndirect.cpp.
* @brief The CopyMemorytIndirect Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "CopyMemorytIndirect.h"

namespace Neptune::Vulkan::Extension {

    CopyMemorytIndirect::CopyMemorytIndirect(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_KHR_COPY_MEMORY_INDIRECT_EXTENSION_NAME);
    }

}

#endif