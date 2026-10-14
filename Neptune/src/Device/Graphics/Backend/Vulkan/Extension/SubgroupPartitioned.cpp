/**
* @file SubgroupPartitioned.cpp.
* @brief The SubgroupPartitioned Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SubgroupPartitioned.h"

namespace Neptune::Vulkan::Extension {
    
    SubgroupPartitioned::SubgroupPartitioned(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_EXT_SHADER_SUBGROUP_PARTITIONED_EXTENSION_NAME);
    }
    
    void SubgroupPartitioned::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_SubgroupPartitionedFeatures);
    }
    
    bool SubgroupPartitioned::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "SubgroupPartitioned [ shaderSubgroupPartitioned ] : " << m_SubgroupPartitionedFeatures.shaderSubgroupPartitioned;
        
        if (!m_SubgroupPartitionedFeatures.shaderSubgroupPartitioned)
        {
            return false;
        }

        return true;
    }
}

#endif