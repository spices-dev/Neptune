/**
* @file TimelineSemaphore.cpp.
* @brief The TimelineSemaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "TimelineSemaphore.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

    TimelineSemaphore::TimelineSemaphore(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void TimelineSemaphore::Create()
    {
        NEPTUNE_PROFILE_ZONE

        VkSemaphoreTypeCreateInfo          timelineInfo{};
        timelineInfo.sType               = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
        timelineInfo.semaphoreType       = VK_SEMAPHORE_TYPE_TIMELINE;
        timelineInfo.initialValue        = 0;
        timelineInfo.pNext               = nullptr;
        
        VkSemaphoreCreateInfo              semaphoreInfo {};
        semaphoreInfo.sType              = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        semaphoreInfo.flags              = 0;
        semaphoreInfo.pNext              = &timelineInfo;
        
        m_Semaphore.CreateSemaphore(GetContext().Get<IDevice>()->Handle(), semaphoreInfo);

        DEBUGUTILS_SETOBJECTNAME(m_Semaphore, ToString())
    }
    
    void TimelineSemaphore::Wait(uint64_t value) const
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Semaphore.Wait(value);
    }

}

#endif