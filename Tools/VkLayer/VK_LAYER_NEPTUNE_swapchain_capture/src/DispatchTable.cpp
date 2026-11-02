/**
* @file DispatchTable.cpp.
* @brief The DispatchTable Class Implementation.
* @author Spices.
*/

#include "DispatchTable.h"

namespace Neptune {
    
    VkResult DispatchTable::vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
    {
        ACCURE_DEVICE_FN(vkCreateSwapchainKHR, device)
        
        Context                    context;
        context.info             = *pCreateInfo;
        context.info.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        
        auto result = std::invoke(vkCreateSwapchainKHR, device, &context.info, pAllocator, pSwapchain);
        
        if (result != VK_SUCCESS) return result;
        
        PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR = nullptr;
        
        {
            std::unique_lock lock(s_Mutex);
            
            auto key = GetKey(device);
            
            context.physicalDevice   = s_DeviceTable.at(key).vkPhysicalDevice;
            context.device           = s_DeviceTable.at(key).vkDevice;
            vkGetSwapchainImagesKHR  = s_DeviceTable.at(key).vkGetSwapchainImagesKHR;
        }
        
        uint32_t imageCount = 0;

        VULKAN_CHECK(vkGetSwapchainImagesKHR(device, *pSwapchain, &imageCount, nullptr))
        
        context.images.resize(imageCount);

        VULKAN_CHECK(vkGetSwapchainImagesKHR(device, *pSwapchain, &imageCount, context.images.data()))

        {
            VkCommandPoolCreateInfo           info{};
            info.sType                      = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            info.flags                      = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            info.queueFamilyIndex           = 0;
        
            vkCreateCommandPool(context.device, &info, pAllocator, &context.commandPool);
        }
        
        {
            VkCommandBufferAllocateInfo        info{};
            info.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            info.commandPool                 = context.commandPool;
            info.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            info.commandBufferCount          = 1;
            
            vkAllocateCommandBuffers(context.device, &info, &context.commandBuffer);
        }
        
        s_Contexts.emplace(*pSwapchain, std::move(context));
        
        return VK_SUCCESS;
    }

    void DispatchTable::vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
    {
        ACCURE_DEVICE_FN(vkDestroySwapchainKHR, device)
        
        s_Contexts.erase(s_Contexts.find(swapchain));
        
        std::invoke(vkDestroySwapchainKHR, device, swapchain, pAllocator);
    }

    VkResult DispatchTable::vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
    {
        ACCURE_DEVICE_FN(vkQueuePresentKHR, queue)
        
        const auto& context = s_Contexts.at(*pPresentInfo->pSwapchains);
        
        {
            VkCommandBufferBeginInfo          info{};
            info.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            info.flags                      = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            info.pInheritanceInfo           = nullptr;
        
            vkBeginCommandBuffer(context.commandBuffer, &info);
        }
        
        {
            
            VkBufferImageCopy          region{};
            region.bufferOffset      = 0;
            region.bufferRowLength   = 0;
            region.bufferImageHeight = 0;
            region.imageSubresource  = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
            region.imageOffset       = { 0, 0, 0 };
            region.imageExtent       = { context.info.imageExtent.width, context.info.imageExtent.height, 1 };
            
            vkCmdCopyImageToBuffer(context.commandBuffer, context.images[*pPresentInfo->pImageIndices], VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, context.buffer, 1, &region);
        }
        
        {
            vkEndCommandBuffer(context.commandBuffer);
        }
        
        {
            VkPipelineStageFlags             flag = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
            
            VkSubmitInfo                     info{};
            info.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            info.waitSemaphoreCount        = pPresentInfo->waitSemaphoreCount;
            info.pWaitSemaphores           = pPresentInfo->pWaitSemaphores;
            info.pWaitDstStageMask         = &flag;
            info.commandBufferCount        = 1;
            info.pCommandBuffers           = &context.commandBuffer;
            info.signalSemaphoreCount      = 1;
            info.pSignalSemaphores         = &context.semaphore;
            
            vkQueueSubmit(queue, 1, &info, VK_NULL_HANDLE);
        }
        
        VkPresentInfoKHR presentInfo       = *pPresentInfo;
        presentInfo.waitSemaphoreCount     = 1;
        presentInfo.pWaitSemaphores        = &context.semaphore;
        
        VULKAN_CHECK(std::invoke(vkQueuePresentKHR, queue, &presentInfo))
        
        VkDevice device = nullptr;
        
        {
            std::unique_lock lock(s_Mutex);
            
            device = s_DeviceTable.at(GetKey(queue)).vkDevice;
        }
        
        VULKAN_CHECK(vkDeviceWaitIdle(device))
        
        
        
        return VK_SUCCESS;
    }
}
