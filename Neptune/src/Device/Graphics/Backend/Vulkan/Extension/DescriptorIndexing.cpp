/**
* @file DescriptorIndexing.cpp.
* @brief The DescriptorIndexing Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DescriptorIndexing.h"

namespace Neptune::Vulkan::Extension {
    
    void DescriptorIndexing::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_DescriptorIndexingFeatures.sType))
        {
            *pNext = &m_DescriptorIndexingFeatures;

            pNext  = &m_DescriptorIndexingFeatures.pNext;
        }
    }
    
    bool DescriptorIndexing::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "DescriptorIndexing [ descriptorBindingPartiallyBound ] : " << m_DescriptorIndexingFeatures.descriptorBindingPartiallyBound;
        NEPTUNE_LOG_CORE(I) << "DescriptorIndexing [ descriptorBindingSampledImageUpdateAfterBind ] : " << m_DescriptorIndexingFeatures.descriptorBindingSampledImageUpdateAfterBind;

        if (!m_DescriptorIndexingFeatures.descriptorBindingPartiallyBound)
        {
            return false;
        }

        if (!m_DescriptorIndexingFeatures.descriptorBindingSampledImageUpdateAfterBind)
        {
            return false;
        }
        
        return true;
    }
}

#endif