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

        std::invoke(m_Life.destructor, m_Device, m_Handle, m_Life.allocator);
    }
    
    void SwapChain::CreateSwapchain(VkDevice device, const VkSwapchainCreateInfoKHR& createInfo)
    {
        m_Device = device;
        
        VULKAN_CHECK(std::invoke(m_Life.constructor, device, &createInfo, m_Life.allocator, &m_Handle))
    }
}