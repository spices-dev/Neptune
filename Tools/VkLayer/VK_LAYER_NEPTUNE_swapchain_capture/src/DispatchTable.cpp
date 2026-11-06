/**
* @file DispatchTable.cpp.
* @brief The DispatchTable Class Implementation.
* @author Spices.
*/

#include "DispatchTable.h"

namespace Neptune {

    VkResult DispatchTable::vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
    {
        ACCURE_DEVICE(deviceTable, device)
        
        auto info = *pCreateInfo;
        
        info.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        
        {
            auto unit = Vulkan::CreateUP<Vulkan::Unit::SwapChain>();
        
            {
                unit->SetHandle(*pSwapchain);
                
                unit->SetLife({deviceTable.vkCreateSwapchainKHR, deviceTable.vkDestroySwapchainKHR, pAllocator });

                unit->CreateSwapchain(device, info);
                
                *pSwapchain = unit->GetHandle();
            }
        
            auto swapChain = Vulkan::CreateUP<Vulkan::SwapChain>();
        
            {
                swapChain->m_SwapChain = std::move(unit);
                
                swapChain->m_Info = info;
                
                swapChain->m_Family = *info.pQueueFamilyIndices;
                
                uint32_t imageCount = 0;

                VULKAN_CHECK(deviceTable.vkGetSwapchainImagesKHR(device, *pSwapchain, &imageCount, nullptr))
        
                swapChain->m_Images.resize(imageCount);

                VULKAN_CHECK(deviceTable.vkGetSwapchainImagesKHR(device, *pSwapchain, &imageCount, swapChain->m_Images.data()))
            }
            
            s_Context.Get<Vulkan::ISwapChain>()->Registry(swapChain->Handle(), std::move(swapChain));
        }
        
        uint32_t family = *info.pQueueFamilyIndices;
        
        if (s_Context.Get<Vulkan::ICommandBuffer>()->Has(family)) return VK_SUCCESS;
        
        {
            auto unitCommandPool = Vulkan::CreateUP<Vulkan::Unit::CommandPool>();
        
            {
                unitCommandPool->SetLife({deviceTable.vkCreateCommandPool, deviceTable.vkDestroyCommandPool, pAllocator });

                VkCommandPoolCreateInfo               poolInfo{};
                poolInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
                poolInfo.flags                      = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
                poolInfo.queueFamilyIndex           = family;
                
                unitCommandPool->CreateCommandPool(device, poolInfo);
            }
            
            auto unitCommandBuffer = Vulkan::CreateUP<Vulkan::Unit::CommandBuffer>();
        
            {
                unitCommandBuffer->SetLife({deviceTable.vkAllocateCommandBuffers, deviceTable.vkFreeCommandBuffers, pAllocator });

                VkCommandBufferAllocateInfo             allocInfo{};
                allocInfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                allocInfo.commandPool                 = unitCommandPool->GetHandle();
                allocInfo.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                allocInfo.commandBufferCount          = 1;
                
                unitCommandBuffer->CreateCommandBuffer(device, allocInfo);
            }
            
            auto unitSemaphore = Vulkan::CreateUP<Vulkan::Unit::Semaphore>();
        
            {
                unitSemaphore->SetLife({deviceTable.vkCreateSemaphore, deviceTable.vkDestroySemaphore, pAllocator });

                VkSemaphoreCreateInfo              semaphoreInfo {};
                semaphoreInfo.sType              = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
                
                unitSemaphore->CreateSemaphore(device, semaphoreInfo);
            }
            
            auto commandBuffer = Vulkan::CreateUP<Vulkan::CommandBuffer>();
        
            {
                commandBuffer->m_CommandPool   = std::move(unitCommandPool);
                commandBuffer->m_CommandBuffer = std::move(unitCommandBuffer);
                commandBuffer->m_Semaphore     = std::move(unitSemaphore);
            }

            s_Context.Get<Vulkan::ICommandBuffer>()->Registry(family, std::move(commandBuffer));
        }
        
        return VK_SUCCESS;
    }

    void DispatchTable::vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
    {
        auto family = s_Context.Get<Vulkan::ISwapChain>()->Get(swapchain).m_Family;
        
        s_Context.Get<Vulkan::ISwapChain>()->UnRegistry(swapchain);
        
        bool inuse = false;
        
        s_Context.Get<Vulkan::ISwapChain>()->View([&](const auto& instance) {
            if (instance->m_Family == family && instance->Handle() != swapchain) inuse |= true;
        });
        
        if (inuse) return;
        
        s_Context.Get<Vulkan::ICommandBuffer>()->UnRegistry(family);
    }

    VkResult DispatchTable::vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
    {
        ACCURE_DEVICE(device, queue)
        
        uint32_t family = 0;
        
        {
            s_Context.Get<Vulkan::ISwapChain>()->View([&](const auto& instance) {
                if (instance->Handle() == *pPresentInfo->pSwapchains) family = instance->m_Family;
            });
        }
        
        const auto& commandBuffer = s_Context.Get<Vulkan::ICommandBuffer>()->Get(family);
        
        {
            VkCommandBufferBeginInfo          info{};
            info.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            info.flags                      = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            info.pInheritanceInfo           = nullptr;
        
            std::invoke(device.vkBeginCommandBuffer, commandBuffer.Handle(), &info);
        }
        
        /*{
            
            VkBufferImageCopy          region{};
            region.bufferOffset      = 0;
            region.bufferRowLength   = 0;
            region.bufferImageHeight = 0;
            region.imageSubresource  = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
            region.imageOffset       = { 0, 0, 0 };
            region.imageExtent       = { context.info.imageExtent.width, context.info.imageExtent.height, 1 };
            
            vkCmdCopyImageToBuffer(context.commandBuffer, context.images[*pPresentInfo->pImageIndices], VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, context.buffer, 1, &region);
        }*/
        
        {
            std::invoke(device.vkEndCommandBuffer, commandBuffer.Handle());
        }
        
        {
            VkPipelineStageFlags             flag = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
            
            VkSubmitInfo                     info{};
            info.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            info.waitSemaphoreCount        = pPresentInfo->waitSemaphoreCount;
            info.pWaitSemaphores           = pPresentInfo->pWaitSemaphores;
            info.pWaitDstStageMask         = &flag;
            info.commandBufferCount        = 1;
            info.pCommandBuffers           = &commandBuffer.Handle();
            info.signalSemaphoreCount      = 1;
            info.pSignalSemaphores         = &commandBuffer.Semaphore();
            
            std::invoke(device.vkQueueSubmit, queue, 1, &info, VK_NULL_HANDLE);
        }
        
        VkPresentInfoKHR presentInfo       = *pPresentInfo;
        presentInfo.waitSemaphoreCount     = 1;
        presentInfo.pWaitSemaphores        = &commandBuffer.Semaphore();
        
        VULKAN_CHECK(std::invoke(device.vkQueuePresentKHR, queue, &presentInfo))
        
        VULKAN_CHECK(std::invoke(device.vkDeviceWaitIdle, device.Handle()))
        
        return VK_SUCCESS;
    }
}
