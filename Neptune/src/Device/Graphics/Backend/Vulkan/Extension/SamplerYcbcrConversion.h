/**
* @file SamplerYcbcrConversion.h.
* @brief The SamplerYcbcrConversion Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using ISamplerYcbcrConversion = IExtension<class SamplerYcbcrConversion, EExtension::SamplerYcbcrConversion>;
    
    class SamplerYcbcrConversion : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        SamplerYcbcrConversion();
        
        /**
        * @brief Destructor Function.
        */
        ~SamplerYcbcrConversion() override = default;
                
        /**
        * @brief Build Device Feature Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        void BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) override;

        /**
        * @brief Combine Device Features.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied() override;
        
    private:
        
        VkPhysicalDeviceSamplerYcbcrConversionFeatures m_SamplerYcbcrConversionFeatures { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES };  // @brief SamplerYcbcrConversionFeatures.
    };
}

#endif