/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/
#include "Buffer.h"

namespace Neptune::Vulkan::Unit {

    Buffer::~Buffer()
    {
        if (!m_Handle) return;

        m_Life.destructor(m_Device, m_Handle, m_Life.allocator);
    }

    VkResult Buffer::CreateBuffer(VkDevice device, const VkBufferCreateInfo& info)
    {
        m_Device = device;

        return m_Life.constructor(m_Device, &info, m_Life.allocator, &m_Handle);
    }
}