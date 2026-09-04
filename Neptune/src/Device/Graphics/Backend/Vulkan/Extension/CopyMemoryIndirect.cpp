/**
* @file CopyMemoryIndirect.cpp.
* @brief The CopyMemoryIndirect Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "CopyMemoryIndirect.h"

namespace Neptune::Vulkan::Extension {

    CopyMemoryIndirect::CopyMemoryIndirect(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_KHR_COPY_MEMORY_INDIRECT_EXTENSION_NAME);
    }

}

#endif