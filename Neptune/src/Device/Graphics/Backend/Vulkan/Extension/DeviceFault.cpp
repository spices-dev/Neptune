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
        
        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_KHR_DEVICE_FAULT_EXTENSION_NAME);
    }
    
    void DeviceFault::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_FaultFeatures.sType))
        {
            *pNext = &m_FaultFeatures;

            pNext  = &m_FaultFeatures.pNext;

            *pNext = nullptr;
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