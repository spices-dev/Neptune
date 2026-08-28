/**
* @file Extension.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Extension.h"

namespace Neptune::Vulkan::Extension {

    void Extension::AddInstanceExtensions(const char* name, bool value)
    {
        NEPTUNE_PROFILE_ZONE

        m_InstanceExtensions.emplace(name, value);
    }
    
    void Extension::AddDeviceExtensions(const char* name, bool value)
    {
        NEPTUNE_PROFILE_ZONE

        m_DeviceExtensions.emplace(name, value);
    }
}

#endif