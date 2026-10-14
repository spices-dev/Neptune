/**
* @file SubgroupSizeControl.cpp.
* @brief The SubgroupSizeControl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SubgroupSizeControl.h"

namespace Neptune::Vulkan::Extension {
    
    SubgroupSizeControl::SubgroupSizeControl(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_EXT_SUBGROUP_SIZE_CONTROL_EXTENSION_NAME);
    }
    
    void SubgroupSizeControl::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan13Features);
    }
    
    void SubgroupSizeControl::BuildPropertyChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE
        
        LinkToChain(pNext, filter, m_SubgroupSizeControlProperties);
    }
    
    bool SubgroupSizeControl::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan13 [ subgroupSizeControl ] : " << m_Vulkan13Features.subgroupSizeControl;
        
        if (!m_Vulkan13Features.subgroupSizeControl)
        {
            return false;
        }

        return true;
    }
    
    bool SubgroupSizeControl::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "SubgroupSizeControl [ minSubgroupSize ] : " << m_SubgroupSizeControlProperties.minSubgroupSize;
        
        if (m_SubgroupSizeControlProperties.minSubgroupSize < 32)
        {
            return false;
        }

        return true;
    }
}

#endif