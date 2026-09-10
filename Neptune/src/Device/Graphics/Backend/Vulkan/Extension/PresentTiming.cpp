/**
* @file PresentTiming.cpp.
* @brief The PresentTiming Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "PresentTiming.h"

namespace Neptune::Vulkan::Extension {
    
    PresentTiming::PresentTiming(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if constexpr (IsCoreExtension<decltype(*this)>) return;
        
        AddDeviceExtensions(VK_KHR_PRESENT_ID_2_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_CALIBRATED_TIMESTAMPS_EXTENSION_NAME);
        AddDeviceExtensions(VK_EXT_PRESENT_TIMING_EXTENSION_NAME);
    }
    
    void PresentTiming::BuildSurfaceCapabilitiesChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_PresentTimingSurfaceCapabilities);
    }
    
    bool PresentTiming::IsSurfaceCapabilitiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "PresentTimingSurfaceCapabilities [ presentTimingSupported ] : " << m_PresentTimingSurfaceCapabilities.presentTimingSupported;
        
        if (!m_PresentTimingSurfaceCapabilities.presentTimingSupported)
        {
            return false;
        }

        return true;
    }
}

#endif