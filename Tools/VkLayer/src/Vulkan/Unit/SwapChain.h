/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::SwapChain Class.
    * This class defines the Vulkan::Unit::SwapChain behaves.
    */
    class SwapChain : public Unit<VkSwapchainKHR, PFN_vkCreateSwapchainKHR, PFN_vkDestroySwapchainKHR>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        SwapChain() = default;

        /**
        * @brief Destructor Function.
        */
        ~SwapChain() override;
        
        /**
        * @brief Create Swapchain.
        *
        * @param[in] device VkDevice.
        * @param[in] createInfo VkSwapchainCreateInfoKHR.
        * 
        * @return Returns VkResult.
        */
        VkResult CreateSwapchain(VkDevice device, const VkSwapchainCreateInfoKHR& createInfo);
        
    private:
        
        VkDevice m_Device = VK_NULL_HANDLE;     // @brief VkDevice
    };
}