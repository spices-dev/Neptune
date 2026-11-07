/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "SwapChain.h"

namespace Neptune::Vulkan::Unit {

    SwapChain::~SwapChain()
    {
        if (!m_Handle) return;

        m_Life.destructor(m_Device, m_Handle, m_Life.allocator);
    }
    
    VkResult SwapChain::CreateSwapchain(VkDevice device, const VkSwapchainCreateInfoKHR& createInfo)
    {
        m_Device = device;
        
        return m_Life.constructor(device, &createInfo, m_Life.allocator, &m_Handle);
    }
}