/**
* @file Vulkan14.cpp.
* @brief The Vulkan14 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Vulkan14.h"

namespace Neptune::Vulkan::Extension {
    
    void Vulkan14::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan14Features);
    }
    
    bool Vulkan14::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        return true;
    }
}

#endif