/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Device.h"

namespace Neptune::Vulkan::Unit {

	Device::~Device()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyDevice(m_Handle, GetAllocator());
	}

	void Device::CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* createInfo)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(physicalDevice && createInfo && !m_Handle)

		VULKAN_CHECK(vkCreateDevice(physicalDevice, createInfo, GetAllocator(), &m_Handle))
	}

	VkQueue Device::GetDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex) const
	{
		NEPTUNE_PROFILE_ZONE

		VkQueue queue{};

		vkGetDeviceQueue(m_Handle, queueFamilyIndex, queueIndex, &queue);

		NEPTUNE_ASSERT(queue)

		return queue;
	}

	void Device::Wait() const
	{
		NEPTUNE_PROFILE_ZONE

		VULKAN_CHECK(vkDeviceWaitIdle(m_Handle))
	}
}

#endif