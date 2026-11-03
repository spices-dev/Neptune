/**
* @file Semaphore.cpp.
* @brief The Semaphore Class Implementation.
* @author Spices.
*/
#include "Semaphore.h"

namespace Neptune::Vulkan::Unit {

    Semaphore::~Semaphore()
    {
        if (!m_Handle) return;

        std::invoke(m_Life.destructor, m_Device, m_Handle, m_Life.allocator);
    }

    void Semaphore::CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& info)
    {
        m_Device = device;

        VULKAN_CHECK(std::invoke(m_Life.constructor, m_Device, &info, m_Life.allocator, &m_Handle))
    }
}