/**
* @file DescriptorHeap.cpp.
* @brief The DescriptorHeap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DescriptorHeap.h"

namespace Neptune::Vulkan::Extension {
    
    DescriptorHeap::DescriptorHeap(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddDeviceExtensions(VK_EXT_DESCRIPTOR_HEAP_EXTENSION_NAME);
    }
    
    void DescriptorHeap::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_DescriptorHeapFeatures.sType))
        {
            *pNext = &m_DescriptorHeapFeatures;

            pNext  = &m_DescriptorHeapFeatures.pNext;
        }
    }
    
    bool DescriptorHeap::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "DescriptorHeap [ descriptorHeap ] : " << m_DescriptorHeapFeatures.descriptorHeap;
        NEPTUNE_LOG_CORE(I) << "DescriptorHeap [ descriptorHeapCaptureReplay ] : " << m_DescriptorHeapFeatures.descriptorHeapCaptureReplay;
        
        if (!m_DescriptorHeapFeatures.descriptorHeap)
        {
            return false;
        }

        return true;
    }
}

#endif