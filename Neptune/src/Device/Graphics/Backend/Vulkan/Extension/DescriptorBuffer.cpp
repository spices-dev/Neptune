/**
* @file DescriptorBuffer.cpp.
* @brief The DescriptorBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DescriptorBuffer.h"

namespace Neptune::Vulkan::Extension {
    
    DescriptorBuffer::DescriptorBuffer(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddDeviceExtensions(VK_EXT_DESCRIPTOR_BUFFER_EXTENSION_NAME);
    }
    
    void DescriptorBuffer::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_DescriptorBufferFeatures.sType))
        {
            *pNext = &m_DescriptorBufferFeatures;

            pNext  = &m_DescriptorBufferFeatures.pNext;
        }
    }
    
    bool DescriptorBuffer::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "DescriptorBuffer [ descriptorBuffer ] : " << m_DescriptorBufferFeatures.descriptorBuffer;
        NEPTUNE_LOG_CORE(I) << "DescriptorBuffer [ descriptorBufferCaptureReplay ] : " << m_DescriptorBufferFeatures.descriptorBufferCaptureReplay;
        
        if (!m_DescriptorBufferFeatures.descriptorBuffer)
        {
            return false;
        }

        return true;
    }
}

#endif