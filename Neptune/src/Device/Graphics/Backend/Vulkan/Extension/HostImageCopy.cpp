/**
* @file HostImageCopy.cpp.
* @brief The HostImageCopy Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "HostImageCopy.h"

namespace Neptune::Vulkan::Extension {
    
    HostImageCopy::HostImageCopy(EExtensionState state)
        : Extension(state)
    {}
    
    void HostImageCopy::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan14Features);
    }
    
    bool HostImageCopy::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan14 [ hostImageCopy ] : " << m_Vulkan14Features.hostImageCopy;

        if (!m_Vulkan14Features.hostImageCopy)
        {
            return false;
        }
        
        return true;
    }
}

#endif