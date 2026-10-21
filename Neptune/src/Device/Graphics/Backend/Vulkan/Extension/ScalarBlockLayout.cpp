/**
* @file ScalarBlockLayout.cpp.
* @brief The ScalarBlockLayout Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ScalarBlockLayout.h"

namespace Neptune::Vulkan::Extension {
    
    ScalarBlockLayout::ScalarBlockLayout(EExtensionState state)
        : Extension(state)
    {}
    
    void ScalarBlockLayout::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan12Features);
    }
    
    bool ScalarBlockLayout::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan12 [ scalarBlockLayout ] : " << m_Vulkan12Features.scalarBlockLayout;
        
        if (!m_Vulkan12Features.scalarBlockLayout)
        {
            return false;
        }

        return true;
    }
    
}

#endif