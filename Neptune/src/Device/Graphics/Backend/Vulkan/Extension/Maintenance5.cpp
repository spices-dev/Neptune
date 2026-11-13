/**
* @file Maintenance5.cpp.
* @brief The Maintenance5 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Maintenance5.h"

namespace Neptune::Vulkan::Extension {
    
    Maintenance5::Maintenance5(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_MAINTENANCE_5_EXTENSION_NAME);
    }
    
    void Maintenance5::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan14Features);
    }
    
    bool Maintenance5::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan14 [ maintenance5 ] : " << m_Vulkan14Features.maintenance5;

        if (!m_Vulkan14Features.maintenance5)
        {
            return false;
        }
        
        return true;
    }
}

#endif