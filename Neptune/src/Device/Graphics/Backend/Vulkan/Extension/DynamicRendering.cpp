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

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME);
    }

    void DynamicRendering::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_Vulkan13Features.sType))
        {
            *pNext = &m_Vulkan13Features;

            pNext  = &m_Vulkan13Features.pNext;
        }
    }
    
    bool DynamicRendering::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan13 [ dynamicRendering ] : " << m_Vulkan13Features.dynamicRendering;
        
        if (!m_Vulkan13Features.dynamicRendering)
        {
            return false;
        }

        return true;
    }

}

#endif