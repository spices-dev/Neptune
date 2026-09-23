/**
* @file Extension.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Extension.h"

namespace Neptune::Vulkan::Extension {

    namespace {
        
        uint32_t s_ApiVersion = VK_DEV_VERSION;       // @brief Api Version.
    }
    
    void Extension::SetApiVersion(uint32_t version)
    {
        NEPTUNE_PROFILE_ZONE
        
        s_ApiVersion = version;
    }
    
    uint32_t Extension::GetApiVersion() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return s_ApiVersion;
    }
    
    void Extension::AddInstanceExtensions(const std::string& name, bool value)
    {
        NEPTUNE_PROFILE_ZONE

        m_InstanceExtensions.insert_or_assign(name, value);
    }
    
    void Extension::AddDeviceExtensions(const std::string& name, bool value)
    {
        NEPTUNE_PROFILE_ZONE

        m_DeviceExtensions.insert_or_assign(name, value);
    }
}

#endif