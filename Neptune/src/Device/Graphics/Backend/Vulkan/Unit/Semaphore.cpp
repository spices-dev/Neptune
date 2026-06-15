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

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateSemaphore(device, &info, GetAllocator(), &m_Handle))
	}
}

#endif