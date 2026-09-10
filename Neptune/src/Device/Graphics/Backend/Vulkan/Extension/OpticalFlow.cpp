/**
* @file OpticalFlow.cpp.
* @brief The OpticalFlow Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "OpticalFlow.h"

namespace Neptune::Vulkan::Extension {
    
    OpticalFlow::OpticalFlow(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_NV_OPTICAL_FLOW_EXTENSION_NAME);
    }
    
    void OpticalFlow::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_OpticalFlowFeatures);
    }
    
    void OpticalFlow::BuildPropertyChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (std::invoke(filter, m_OpticalFlowProperties.sType))
        {
            *pNext = &m_OpticalFlowProperties;

            pNext  = &m_OpticalFlowProperties.pNext;
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
    
    bool OpticalFlow::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "OpticalFlow [ globalFlowSupported ] : " << m_OpticalFlowProperties.globalFlowSupported;
        
        if (!m_OpticalFlowProperties.globalFlowSupported)
        {
            return false;
        }

        return true;
    }
}

#endif