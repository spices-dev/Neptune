/**
* @file Queue.cpp.
* @brief The Queue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Queue.h"
#include "CommandBuffer.h"

namespace Neptune::Vulkan::Unit {

	void Queue::Submit(const VkSubmitInfo& info, VkFence fence) const
	{
		NEPTUNE_PROFILE_ZONE

		VULKAN_CHECK(vkQueueSubmit(m_Handle, 1, &info, fence))
	}

	void Queue::Submit2(const VkSubmitInfo2& info, VkFence fence) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VULKAN_CHECK(vkQueueSubmit2(m_Handle, 1, &info, fence))
	}
	
	void Queue::Wait() const
	{
		NEPTUNE_PROFILE_ZONE

		VULKAN_CHECK(vkQueueWaitIdle(m_Handle))
	}
}

#endif