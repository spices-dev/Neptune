/**
* @file SamplerYcbcrConversion.cpp.
* @brief The SamplerYcbcrConversion Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SamplerYcbcrConversion.h"

namespace Neptune::Vulkan::Extension {
    
    SamplerYcbcrConversion::SamplerYcbcrConversion(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_SAMPLER_YCBCR_CONVERSION_EXTENSION_NAME);
    }
    
    void SamplerYcbcrConversion::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan11Features);
    }
    
    bool SamplerYcbcrConversion::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan11 [ samplerYcbcrConversion ] : " << m_Vulkan11Features.samplerYcbcrConversion;
        
        if (!m_Vulkan11Features.samplerYcbcrConversion)
        {
            return false;
        }

        return true;
    }
}

#endif