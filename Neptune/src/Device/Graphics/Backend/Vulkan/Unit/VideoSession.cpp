/**
* @file VideoSession.cpp.
* @brief The VideoSession Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "VideoSession.h"

namespace Neptune::Vulkan::Unit {

	VideoSession::~VideoSession()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyVideoSessionKHR(m_Device, m_Handle, GetAllocator());

		for (int i = 0 ; i < m_Memories.size(); i++)
		{
			FreeMemory(m_Device, m_Memories[i], GetAllocator(), m_Flags);
		}
	}

	void VideoSession::CreateVideoSession(VkDevice device, const VkVideoSessionCreateInfoKHR& createInfo)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(device && !m_Handle)

		m_Device = device;

		VULKAN_CHECK(vkCreateVideoSessionKHR(m_Device, &createInfo, GetAllocator(), &m_Handle))
	}

	VkDeviceMemory VideoSession::AllocateMemory(const VkMemoryAllocateInfo& info, VkMemoryPropertyFlags flags)
	{
		NEPTUNE_PROFILE_ZONE

		VkDeviceMemory memory = VK_NULL_HANDLE;

		m_Flags = flags;
		
		Vulkan::AllocateMemory(m_Device, &info, GetAllocator(), &memory, flags);

		m_Memories.emplace_back(memory);

		return memory;
	}

	void VideoSession::BindVideoSessionMemory(const std::vector<VkBindVideoSessionMemoryInfoKHR>& infos) const
	{
		NEPTUNE_PROFILE_ZONE

		VULKAN_CHECK(vkBindVideoSessionMemoryKHR(m_Device, m_Handle, infos.size(), infos.data()))
	}
}

#endif