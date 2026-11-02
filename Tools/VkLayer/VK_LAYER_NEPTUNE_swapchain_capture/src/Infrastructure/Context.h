/**
* @file Context.h.
* @brief The Context Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <vector>

namespace Neptune::Vulkan {
    
    /**
    * @brief This Layer Context Data
    */
    struct Context
    {
        VkPhysicalDevice         physicalDevice;     // @brief VkPhysicalDevice.
        VkDevice                 device;             // @brief VkDevice.
        std::vector<VkImage>     images;             // @brief SwapChain Images.
        VkBuffer                 buffer;             // @brief SwapChain Image Transfer Buffer.
        VkSwapchainCreateInfoKHR info;               // @brief VkSwapchainCreateInfoKHR.
        VkCommandPool            commandPool;        // @brief VkCommandPool.
        VkCommandBuffer          commandBuffer;      // @brief VkCommandBuffer.
        VkSemaphore              semaphore;          // @brief VkSemaphore.
    };
}