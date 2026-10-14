/**
* @file SubgroupRotate.cpp.
* @brief The SubgroupRotate Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SubgroupRotate.h"

namespace Neptune::Vulkan::Extension {
    
    SubgroupRotate::SubgroupRotate(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME);
    }
    
    void SubgroupRotate::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_SubgroupRotateFeatures);
    }
    
    bool SubgroupRotate::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "SubgroupRotate [ shaderSubgroupRotate ] : " << m_SubgroupRotateFeatures.shaderSubgroupRotate;
        
        if (!m_SubgroupRotateFeatures.shaderSubgroupRotate)
        {
            return false;
        }

        return true;
    }
}

#endif