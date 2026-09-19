/**
* @file TimeLine2.cpp.
* @brief The TimeLine2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "TimeLine2.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"

namespace Neptune::Vulkan::Middleware {
	
    TimeLine2::TimeLine2(Context& context)
        : ContextAccessor(context)
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	Create();
    }

    void TimeLine2::Wait(uint64_t frameId) const
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	m_Semaphore.Wait(frameId);
    }

	void TimeLine2::Create()
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

    	DEBUGUTILS_SETOBJECTNAME(m_Semaphore, "TimeLineSemaphore")
    }
	
	VkSemaphore TimeLine2::Semaphore(uint64_t frameId) const
    {
    	NEPTUNE_PROFILE_ZONE
		
		return m_Semaphore.GetHandle();
    }
	
	void TimeLine2::SetName(const std::string& name) const
    {
    	NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Semaphore, name + "TimeLineSemaphore")
    }
}

#endif