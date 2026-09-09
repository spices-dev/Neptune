/**
* @file TimelineSemaphore.cpp.
* @brief The TimelineSemaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "TimelineSemaphore.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Vulkan::Resource {

    void TimelineSemaphore::CreateSemaphore()
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
        
        DEBUGUTILS_SETOBJECTNAME(m_Semaphore, "TimelineSemaphore")
    }
	
	void TimelineSemaphore::Wait()
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	m_Semaphore.Wait(m_Id++);
    }
	
	void TimelineSemaphore::Signal() const
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	m_Semaphore.Signal(m_Id);
    }

    void TimelineSemaphore::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE

        DEBUGUTILS_SETOBJECTNAME(m_Semaphore, name)
    }
}

#endif