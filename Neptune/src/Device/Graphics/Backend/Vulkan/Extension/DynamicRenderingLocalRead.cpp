/**
* @file DynamicRenderingLocalRead.cpp.
* @brief The DynamicRenderingLocalRead Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DynamicRenderingLocalRead.h"

namespace Neptune::Vulkan::Extension {

    DynamicRenderingLocalRead::DynamicRenderingLocalRead(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_KHR_DYNAMIC_RENDERING_LOCAL_READ_EXTENSION_NAME);
    }

    void DynamicRenderingLocalRead::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_DynamicRenderingLocalReadFeatures.sType))
        {
            *pNext = &m_DynamicRenderingLocalReadFeatures;

            pNext  = &m_DynamicRenderingLocalReadFeatures.pNext;
        }
    }
    
    bool DynamicRenderingLocalRead::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "DynamicRenderingLocalRead [ dynamicRenderingLocalRead ] : " << m_DynamicRenderingLocalReadFeatures.dynamicRenderingLocalRead;
        
        if (!m_DynamicRenderingLocalReadFeatures.dynamicRenderingLocalRead)
        {
            return false;
        }

        return true;
    }

}

#endif