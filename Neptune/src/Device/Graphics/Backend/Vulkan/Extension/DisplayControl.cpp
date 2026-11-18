/**
* @file DisplayControl.cpp.
* @brief The DisplayControl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DisplayControl.h"

namespace Neptune::Vulkan::Extension {

    DisplayControl::DisplayControl(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddDeviceExtensions(VK_EXT_DISPLAY_CONTROL_EXTENSION_NAME);
    }

}

#endif