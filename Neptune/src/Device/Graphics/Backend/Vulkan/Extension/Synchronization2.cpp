/**
* @file Synchronization2.cpp.
* @brief The Synchronization2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Synchronization2.h"

namespace Neptune::Vulkan::Extension {
    
    Synchronization2::Synchronization2(EExtensionState state)
        : Extension(state)
    {}
    
    void Synchronization2::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_Vulkan13Features.sType))
        {
            *pNext = &m_Vulkan13Features;

            pNext  = &m_Vulkan13Features.pNext;

            *pNext = nullptr;
        }
    }
    
    bool Synchronization2::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan13 [ synchronization2 ] : " << m_Vulkan13Features.synchronization2;
        
        if (!m_Vulkan13Features.synchronization2)
        {
            return false;
        }

        return true;
    }
}

#endif