/**
* @file OpticalFlow.h.
* @brief The OpticalFlow Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IOpticalFlow = IExtension<class OpticalFlow, EExtension::OpticalFlow>;
    
    class OpticalFlow : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        OpticalFlow();
        
        /**
        * @brief Destructor Function.
        */
        ~OpticalFlow() override = default;
        
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
        
        VkPhysicalDeviceOpticalFlowFeaturesNV m_OpticalFlowFeatures { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV };  // @brief OpticalFlowFeatures.
    };
}

#endif