/**
* @file SwapChainMaintenance1.cpp.
* @brief The SwapChainMaintenance1 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SwapChainMaintenance1.h"

namespace Neptune::Vulkan::Extension {
    
    SwapChainMaintenance1::SwapChainMaintenance1(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddInstanceExtensions(VK_KHR_SURFACE_MAINTENANCE_1_EXTENSION_NAME);
        
        AddDeviceExtensions(VK_KHR_SWAPCHAIN_MAINTENANCE_1_EXTENSION_NAME);
    }
    
    void SwapChainMaintenance1::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_SwapchainMaintenance1Features);
    }
    
    bool SwapChainMaintenance1::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "SwapchainMaintenance1 [ swapchainMaintenance1 ] : " << m_SwapchainMaintenance1Features.swapchainMaintenance1;
        
        if (!m_SwapchainMaintenance1Features.swapchainMaintenance1)
        {
            return false;
        }

        return true;
    }
    
}

#endif