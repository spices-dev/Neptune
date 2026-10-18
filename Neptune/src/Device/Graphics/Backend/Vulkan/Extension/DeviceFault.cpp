/**
* @file DeviceFault.cpp.
* @brief The DeviceFault Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DeviceFault.h"

namespace Neptune::Vulkan::Extension {
    
    DeviceFault::DeviceFault(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_DEVICE_FAULT_EXTENSION_NAME);
        AddDeviceExtensions(VK_EXT_DEVICE_FAULT_EXTENSION_NAME);
    }
    
    void DeviceFault::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_FaultFeatureKHRs);
        
        LinkToChain(pNext, filter, m_FaultFeatureEXTs);
    }
    
    bool DeviceFault::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "DeviceFaultKHR [ deviceFault ] : " << m_FaultFeatureKHRs.deviceFault;
        NEPTUNE_LOG_CORE(I) << "DeviceFaultEXT [ deviceFault ] : " << m_FaultFeatureEXTs.deviceFault;
        
        if (!m_FaultFeatureKHRs.deviceFault)
        {
            return false;
        }
        
        if (!m_FaultFeatureEXTs.deviceFault)
        {
            return false;
        }

        return true;
    }
}

#endif