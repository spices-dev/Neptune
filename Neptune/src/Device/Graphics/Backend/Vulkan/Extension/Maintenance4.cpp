/**
* @file Maintenance4.cpp.
* @brief The Maintenance4 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Maintenance4.h"

namespace Neptune::Vulkan::Extension {
    
    Maintenance4::Maintenance4(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_MAINTENANCE_4_EXTENSION_NAME);
    }
    
    void Maintenance4::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan13Features);
    }
    
    bool Maintenance4::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Maintenance4 [ maintenance4 ] : " << m_Vulkan13Features.maintenance4;

        if (!m_Vulkan13Features.maintenance4)
        {
            return false;
        }
        
        return true;
    }
}

#endif