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

        if (std::invoke(filter, m_ScalarBlockLayoutFeatures.sType))
        {
            *pNext = &m_ScalarBlockLayoutFeatures;

            pNext  = &m_ScalarBlockLayoutFeatures.pNext;
        }
    }
    
    bool ScalarBlockLayout::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "ScalarBlockLayout [ scalarBlockLayout ] : " << m_ScalarBlockLayoutFeatures.scalarBlockLayout;
        
        if (!m_ScalarBlockLayoutFeatures.scalarBlockLayout)
        {
            return false;
        }

        return true;
    }
    
}

#endif