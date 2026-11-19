/**
* @file ToolingInfo.cpp.
* @brief The ToolingInfo Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ToolingInfo.h"

namespace Neptune::Vulkan::Extension {
    
    ToolingInfo::ToolingInfo(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_EXT_TOOLING_INFO_EXTENSION_NAME);
    }
    
}

#endif