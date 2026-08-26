/**
* @file OpticalFlow.cpp.
* @brief The OpticalFlow Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "OpticalFlow.h"

namespace Neptune::Vulkan::Extension {
    
    OpticalFlow::OpticalFlow()
    {
        NEPTUNE_PROFILE_ZONE
        
        AddDeviceExtensions(VK_NV_OPTICAL_FLOW_EXTENSION_NAME);
    }
    
    void OpticalFlow::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_OpticalFlowFeatures.sType))
        {
            *pNext = &m_OpticalFlowFeatures;

            pNext  = &m_OpticalFlowFeatures.pNext;
        }
    }
    
    bool OpticalFlow::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "OpticalFlow [ opticalFlow ] : " << m_OpticalFlowFeatures.opticalFlow;
        
        if (!m_OpticalFlowFeatures.opticalFlow)
        {
            return false;
        }

        return true;
    }
}

#endif