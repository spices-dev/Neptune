/**
* @file TimelineSemaphore.cpp.
* @brief The TimelineSemaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "TimelineSemaphore.h"

namespace Neptune::Vulkan::Extension {
    
    TimelineSemaphore::TimelineSemaphore(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME);
    }
    
    void TimelineSemaphore::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_TimelineSemaphoreFeatures);
    }
    
    bool TimelineSemaphore::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "TimelineSemaphore [ timelineSemaphore ] : " << m_TimelineSemaphoreFeatures.timelineSemaphore;
        
        if (!m_TimelineSemaphoreFeatures.timelineSemaphore)
        {
            return false;
        }

        return true;
    }
}

#endif