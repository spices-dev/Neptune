/**
* @file DeviceFault.cpp.
* @brief The DeviceFault Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DeviceFault.h"

namespace Neptune::Vulkan::Extension {
    
    DeviceFault::DeviceFault()
    {
        NEPTUNE_PROFILE_ZONE
        
        AddDeviceExtensions(VK_EXT_DEVICE_FAULT_EXTENSION_NAME);

        AddDeviceFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT);
    }
    
    void DeviceFault::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_FaultFeatures.sType))
        {
            *pNext = &m_FaultFeatures;

            pNext  = &m_FaultFeatures.pNext;
        }
    }
    
    bool DeviceFault::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "DeviceFault [ deviceFault ] : " << m_FaultFeatures.deviceFault;
        
        if (!m_FaultFeatures.deviceFault)
        {
            return false;
        }

        return true;
    }
}

#endif