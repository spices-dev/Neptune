/**
* @file Vulkan11.cpp.
* @brief The Vulkan11 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Vulkan11.h"

namespace Neptune::Vulkan::Extension {
    
    void Vulkan11::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan11Features);
    }
    
    bool Vulkan11::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan11 [ shaderDrawParameters ] : " << m_Vulkan11Features.shaderDrawParameters;

        if (!m_Vulkan11Features.shaderDrawParameters)
        {
            return false;
        }
        
        return true;
    }
}

#endif