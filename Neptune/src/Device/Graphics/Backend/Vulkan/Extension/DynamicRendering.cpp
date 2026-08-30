/**
* @file DynamicRendering.cpp.
* @brief The DynamicRendering Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DynamicRendering.h"

namespace Neptune::Vulkan::Extension {

    DynamicRendering::DynamicRendering(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddDeviceExtensions(VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME);
    }

    void DynamicRendering::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_DynamicRenderingFeatures.sType))
        {
            *pNext = &m_DynamicRenderingFeatures;

            pNext  = &m_DynamicRenderingFeatures.pNext;
        }
    }
    
    bool DynamicRendering::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "DynamicRendering [ dynamicRendering ] : " << m_DynamicRenderingFeatures.dynamicRendering;
        
        if (!m_DynamicRenderingFeatures.dynamicRendering)
        {
            return false;
        }

        return true;
    }

}

#endif