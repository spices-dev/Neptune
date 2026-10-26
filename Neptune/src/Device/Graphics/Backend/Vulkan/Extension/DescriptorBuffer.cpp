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

        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_EXT_DESCRIPTOR_BUFFER_EXTENSION_NAME);
    }
    
    void DescriptorBuffer::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_DescriptorBufferFeatures);
    }
    
    void DescriptorBuffer::BuildPropertyChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE
        
        LinkToChain(pNext, filter, m_DescriptorBufferProperties);
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

    bool DescriptorBuffer::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "DescriptorBuffer [ descriptorBufferOffsetAlignment ] : " << m_DescriptorBufferProperties.descriptorBufferOffsetAlignment;
        NEPTUNE_LOG_CORE(I) << "DescriptorBuffer [ combinedImageSamplerDescriptorSingleArray ] : " << m_DescriptorBufferProperties.combinedImageSamplerDescriptorSingleArray; // False: Image, Image, Sampler, Sampler 

        if (!m_DescriptorBufferProperties.descriptorBufferOffsetAlignment)
        {
            return false;
        }
        
        return true;
    }
}

#endif