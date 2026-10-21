/**
* @file Vulkan12.cpp.
* @brief The Vulkan12 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Vulkan12.h"

namespace Neptune::Vulkan::Extension {
    
    void Vulkan12::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan12Features);
    }
    
    bool Vulkan12::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan12 [ shaderFloat16 ] : " << m_Vulkan12Features.shaderFloat16;

        if (!m_Vulkan12Features.shaderFloat16)
        {
            return false;
        }
        
        return true;
    }
}

#endif