/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Device.h"

namespace Neptune::Vulkan::Unit {

    Device::~Device()
    {
        if (!m_Handle) return;

        std::invoke(m_Life.destructor, m_Handle, m_Life.allocator);
    }
    
    void Device::CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& info)
    {
        VULKAN_CHECK(std::invoke(m_Life.constructor, physicalDevice, &info, m_Life.allocator, &m_Handle))
    }
}