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

        m_Life.destructor(m_Handle, m_Life.allocator);
    }
    
    VkResult Device::CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& info)
    {
        return m_Life.constructor(physicalDevice, &info, m_Life.allocator, &m_Handle);
    }
}