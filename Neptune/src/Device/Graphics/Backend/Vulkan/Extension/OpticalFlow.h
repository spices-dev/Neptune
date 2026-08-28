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
        * @brief Build Device Property Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        void BuildPropertyChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) override;
        
        /**
        * @brief Build Device Queue Chain.
        * 
        * @param[in,out] chains Required Chain.
        */
        void BuildQueueChain(std::unordered_set<VkQueueFlagBits>& chains) override { chains.insert(VK_QUEUE_OPTICAL_FLOW_BIT_NV); }
        
        /**
        * @brief Combine Device Features.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied() override;
        
        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsPropertiesSatisfied() override;
        
    private:
        
        VkPhysicalDeviceOpticalFlowFeaturesNV m_OpticalFlowFeatures { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV };  // @brief OpticalFlowFeatures.
        
        VkPhysicalDeviceOpticalFlowPropertiesNV m_OpticalFlowProperties { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV }; // @brief OpticalFlowProperties.
    };
}

#endif