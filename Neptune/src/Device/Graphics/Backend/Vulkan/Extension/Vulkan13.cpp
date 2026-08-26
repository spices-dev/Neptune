/**
* @file Vulkan13.cpp.
* @brief The Vulkan13 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Vulkan13.h"

namespace Neptune::Vulkan::Extension {
    
    void Vulkan13::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_Vulkan13Features.sType))
        {
            *pNext = &m_Vulkan13Features;

            pNext  = &m_Vulkan13Features.pNext;
        }
    }
    
    bool Vulkan13::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan13 [ shaderDemoteToHelperInvocation ] : " << m_Vulkan13Features.shaderDemoteToHelperInvocation;

        if (!m_Vulkan13Features.shaderDemoteToHelperInvocation)
        {
            return false;
        }
        
        return true;
    }
}

#endif