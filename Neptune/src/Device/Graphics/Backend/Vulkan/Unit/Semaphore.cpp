/**
* @file Semaphore.cpp.
* @brief The Semaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Semaphore.h"

namespace Neptune::Vulkan::Unit {

	Semaphore::~Semaphore()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroySemaphore(m_Device, m_Handle, GetAllocator());
	}

	void Semaphore::CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(device)

		m_Device = device;

		VULKAN_CHECK(vkCreateSemaphore(device, &info, GetAllocator(), &m_Handle))
	}
	
	uint64_t Semaphore::GetValue() const
	{
		NEPTUNE_PROFILE_ZONE
		
		uint64_t value = UINT64_MAX;
		
		VULKAN_CHECK(vkGetSemaphoreCounterValue(m_Device, m_Handle, &value))
		
		return value;
	}
	
	void Semaphore::Wait(uint64_t value) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkSemaphoreWaitInfo           info{};
		info.sType                  = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
		info.flags                  = 0;
		info.semaphoreCount         = 1;
		info.pSemaphores            = &m_Handle;
		info.pValues                = &value;
		info.pNext                  = nullptr;
		
		VULKAN_CHECK(vkWaitSemaphores(m_Device, &info, UINT64_MAX))
	}
	
	void Semaphore::Signal(uint64_t value) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkSemaphoreSignalInfo         info{};
		info.sType                  = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
		info.semaphore              = m_Handle;
		info.value                  = value;
		info.pNext                  = nullptr;
		
		VULKAN_CHECK(vkSignalSemaphore(m_Device, &info))
	}
}

#endif