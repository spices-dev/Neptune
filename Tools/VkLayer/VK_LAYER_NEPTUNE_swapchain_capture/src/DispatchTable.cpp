/**
* @file DispatchTable.cpp.
* @brief The DispatchTable Class Implementation.
* @author Spices.
*/

#include "DispatchTable.h"

namespace Neptune::VkLayer {
    
    namespace {
        
        std::vector<VkImage> s_SwapChainImages;
    }
    
    VkResult DispatchTable::vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
    {
        ACCURE_DEVICE_FN(vkCreateSwapchainKHR, device)
        
        auto info = *pCreateInfo;
        
        info.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        
        auto result = std::invoke(vkCreateSwapchainKHR, device, &info, pAllocator, pSwapchain);
        
        if (result != VK_SUCCESS) return result;
        
        ACCURE_DEVICE_FN(vkGetSwapchainImagesKHR, device)
        
        uint32_t imageCount = 0;

        VULKAN_CHECK(vkGetSwapchainImagesKHR(device, *pSwapchain, &imageCount, nullptr))
        
        s_SwapChainImages.resize(imageCount);

        VULKAN_CHECK(vkGetSwapchainImagesKHR(device, *pSwapchain, &imageCount, s_SwapChainImages.data()))
        
        return VK_SUCCESS;
    }

    void DispatchTable::vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
    {
        ACCURE_DEVICE_FN(vkDestroySwapchainKHR, device)
        
        s_SwapChainImages.clear();
        
        std::invoke(vkDestroySwapchainKHR, device, swapchain, pAllocator);
    }

    VkResult DispatchTable::vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
    {
        ACCURE_DEVICE_FN(vkQueuePresentKHR, queue)
        
        return std::invoke(vkQueuePresentKHR, queue, pPresentInfo);
    }
}
