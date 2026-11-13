/**
* @file Maintenance6.cpp.
* @brief The Maintenance6 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Maintenance6.h"

namespace Neptune::Vulkan::Extension {
    
    Maintenance6::Maintenance6(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_MAINTENANCE_6_EXTENSION_NAME);
    }
    
    void Maintenance6::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan14Features);
    }
    
    bool Maintenance6::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan14 [ maintenance6 ] : " << m_Vulkan14Features.maintenance6;

        if (!m_Vulkan14Features.maintenance6)
        {
            return false;
        }
        
        return true;
    }
}

#endif