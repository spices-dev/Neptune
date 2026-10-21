/**
* @file Subgroup.cpp.
* @brief The Subgroup Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Subgroup.h"

namespace Neptune::Vulkan::Extension {
    
    Subgroup::Subgroup(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;
    }
    
    void Subgroup::BuildPropertyChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE
        
        LinkToChain(pNext, filter, m_SubgroupProperties);
    }
    
    bool Subgroup::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Subgroup [ subgroupSize ] : " << m_SubgroupProperties.subgroupSize;
        NEPTUNE_LOG_CORE(I) << "Subgroup [ supportedOperations ] : " << m_SubgroupProperties.supportedOperations;
        
        if (m_SubgroupProperties.subgroupSize < 32)
        {
            return false;
        }
        
        if (!((m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_BASIC_BIT) && 
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_VOTE_BIT) &&
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_ARITHMETIC_BIT) &&
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_BALLOT_BIT) &&
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_SHUFFLE_BIT) &&
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT) &&
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_CLUSTERED_BIT) &&
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_QUAD_BIT) &&
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_ROTATE_BIT) &&
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_ROTATE_CLUSTERED_BIT) &&
              (m_SubgroupProperties.supportedOperations & VK_SUBGROUP_FEATURE_PARTITIONED_BIT_EXT)))
        {
            return false;
        }

        return true;
    }
}

#endif