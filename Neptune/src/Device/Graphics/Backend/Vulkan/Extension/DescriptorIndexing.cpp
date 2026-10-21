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

        LinkToChain(pNext, filter, m_Vulkan12Features);
    }
    
    bool DescriptorIndexing::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan12 [ descriptorBindingPartiallyBound ] : " << m_Vulkan12Features.descriptorBindingPartiallyBound;
        NEPTUNE_LOG_CORE(I) << "Vulkan12 [ descriptorBindingSampledImageUpdateAfterBind ] : " << m_Vulkan12Features.descriptorBindingSampledImageUpdateAfterBind;

        if (!m_Vulkan12Features.descriptorBindingPartiallyBound)
        {
            return false;
        }

        if (!m_Vulkan12Features.descriptorBindingSampledImageUpdateAfterBind)
        {
            return false;
        }
        
        return true;
    }
}

#endif