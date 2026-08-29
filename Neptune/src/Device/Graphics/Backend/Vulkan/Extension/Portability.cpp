/**
* @file Portability.cpp.
* @brief The Portability Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Portability.h"

namespace Neptune::Vulkan::Extension {
    
    Portability::Portability(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        AddInstanceExtensions(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        
        AddDeviceExtensions(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
    }
    
    void Portability::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_PortabilitySubsetFeatures.sType))
        {
            *pNext = &m_PortabilitySubsetFeatures;

            pNext  = &m_PortabilitySubsetFeatures.pNext;
        }
    }
    
    bool Portability::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE

        return true;
    }
}

#endif