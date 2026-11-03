/**
* @file CommandBuffer.cpp.
* @brief The CommandBuffer Class Implementation.
* @author Spices.
*/
#include "CommandBuffer.h"

namespace Neptune::Vulkan::Unit {

	CommandBuffer::~CommandBuffer()
	{
		if (!m_Handle) return;

		std::invoke(m_Life.destructor, m_Device, m_CommandPool, 1, &m_Handle);
	}

	void CommandBuffer::CreateCommandBuffer(VkDevice device, const VkCommandBufferAllocateInfo& info)
	{
		m_Device = device;
		m_CommandPool = info.commandPool;

		VULKAN_CHECK(std::invoke(m_Life.constructor, m_Device, &info, &m_Handle))
	}
}