/**
* @file CommandPool.cpp.
* @brief The CommandPool Class Implementation.
* @author Spices.
*/
#include "CommandPool.h"

namespace Neptune::Vulkan::Unit {

	CommandPool::~CommandPool()
	{
		if (!m_Handle) return;

		std::invoke(m_Life.destructor, m_Device, m_Handle, m_Life.allocator);
	}

	void CommandPool::CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo& info)
	{
		m_Device = device;

		VULKAN_CHECK(std::invoke(m_Life.constructor, device, &info, m_Life.allocator, &m_Handle))
	}
}