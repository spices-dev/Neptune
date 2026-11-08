/**
* @file DispatchTable.cpp.
* @brief The DispatchTable Class Implementation.
* @author Spices.
*/

#include "DispatchTable.h"
#include "Vulkan/Converter.h"
#include "Asset/ImageWriter.h"

#include <filesystem>

namespace Neptune {

    namespace {
        
        std::filesystem::path MakePath(const std::filesystem::path& dir, uint64_t frame, uint32_t w, uint32_t h)
        {
            char name[128];
            std::snprintf(name, sizeof(name), "SwapChain_%06llu_%ux%u.png", frame, w, h);
            return dir / name;
        }
    }
    
    VkResult DispatchTable::vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
    {
        ACCURE_DEVICE(deviceTable, device)
        
        auto info = *pCreateInfo;
        
        info.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        
        {
            auto unitSwapChain = CreateUP<Vulkan::Unit::SwapChain>();
        
            {
                unitSwapChain->SetHandle(*pSwapchain);
                
                unitSwapChain->SetLife({deviceTable.m_Table.CreateSwapchainKHR, deviceTable.m_Table.DestroySwapchainKHR, pAllocator });

                VULKAN_CHECK(unitSwapChain->CreateSwapchain(device, info))
                
                *pSwapchain = unitSwapChain->GetHandle();
            }

            ACCURE_INSTANCE(instanceTable, deviceTable.vkPhysicalDevice)
        
            auto unitBuffer = CreateUP<Vulkan::Resource::Buffer>(instanceTable, deviceTable);
            
            {
                VkBufferCreateInfo                         bufferInfo{};
                bufferInfo.sType                         = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
                bufferInfo.size                          = info.imageExtent.width * info.imageExtent.height * Vulkan::ToSize(info.imageFormat);
                bufferInfo.usage                         = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
                bufferInfo.flags                         = 0;
                bufferInfo.sharingMode                   = VK_SHARING_MODE_EXCLUSIVE;
                bufferInfo.queueFamilyIndexCount         = 1;
                bufferInfo.pQueueFamilyIndices           = info.pQueueFamilyIndices;
                
                VULKAN_CHECK(unitBuffer->CreateBuffer(bufferInfo, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, pAllocator))
            }
            
            auto swapChain = CreateUP<Vulkan::SwapChain>();
        
            {
                swapChain->m_SwapChain = std::move(unitSwapChain);
                
                swapChain->m_StagingBuffer = std::move(unitBuffer);
                
                swapChain->m_Info = info;
                
                swapChain->m_Family = *info.pQueueFamilyIndices;
            }

            {
                uint32_t imageCount = 0;

                VULKAN_CHECK(deviceTable.m_Table.GetSwapchainImagesKHR(device, *pSwapchain, &imageCount, nullptr))
        
                swapChain->m_Images.resize(imageCount);

                VULKAN_CHECK(deviceTable.m_Table.GetSwapchainImagesKHR(device, *pSwapchain, &imageCount, swapChain->m_Images.data()))
            }
            
            s_Context.Get<Vulkan::ISwapChain>()->Registry(swapChain->Handle(), std::move(swapChain));
        }
        
        uint32_t family = *info.pQueueFamilyIndices;
        
        if (s_Context.Get<Vulkan::ICommandBuffer>()->Has(family)) return VK_SUCCESS;
        
        {
            auto unitCommandPool = CreateUP<Vulkan::Unit::CommandPool>();
        
            {
                unitCommandPool->SetLife({deviceTable.m_Table.CreateCommandPool, deviceTable.m_Table.DestroyCommandPool, pAllocator });

                VkCommandPoolCreateInfo               poolInfo{};
                poolInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
                poolInfo.flags                      = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
                poolInfo.queueFamilyIndex           = family;
                
                VULKAN_CHECK(unitCommandPool->CreateCommandPool(device, poolInfo))
            }
            
            auto unitCommandBuffer = CreateUP<Vulkan::Unit::CommandBuffer>();
        
            {
                unitCommandBuffer->SetLife({deviceTable.m_Table.AllocateCommandBuffers, deviceTable.m_Table.FreeCommandBuffers, pAllocator });

                VkCommandBufferAllocateInfo             allocInfo{};
                allocInfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                allocInfo.commandPool                 = unitCommandPool->GetHandle();
                allocInfo.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                allocInfo.commandBufferCount          = 1;
                
                VULKAN_CHECK(unitCommandBuffer->CreateCommandBuffer(device, allocInfo))
            }
            
            auto unitSemaphore = CreateUP<Vulkan::Unit::Semaphore>();
        
            {
                unitSemaphore->SetLife({deviceTable.m_Table.CreateSemaphore, deviceTable.m_Table.DestroySemaphore, pAllocator });

                VkSemaphoreCreateInfo              semaphoreInfo {};
                semaphoreInfo.sType              = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
                
                VULKAN_CHECK(unitSemaphore->CreateSemaphore(device, semaphoreInfo))
            }
            
            auto commandBuffer = CreateUP<Vulkan::CommandBuffer>();
        
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
        
        const auto& swapChain     = s_Context.Get<Vulkan::ISwapChain>()->Get(*pPresentInfo->pSwapchains);
        const auto& commandBuffer = s_Context.Get<Vulkan::ICommandBuffer>()->Get(swapChain.m_Family);
        
        {
            VkCommandBufferBeginInfo          info{};
            info.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            info.flags                      = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            info.pInheritanceInfo           = nullptr;
        
            device.m_Table.BeginCommandBuffer(commandBuffer.Handle(), &info);
        }
        
        {
            /*{
                VkImageMemoryBarrier             memory{};
                memory.sType                   = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
                memory.srcAccessMask           = ToVkAccessFlags(barrier.srcAccessMask);
                memory.dstAccessMask           = ToVkAccessFlags(barrier.dstAccessMask);
                memory.srcQueueFamilyIndex     = barrier.srcQueueFamilyIndex;
                memory.dstQueueFamilyIndex     = barrier.dstQueueFamilyIndex;
                memory.image                   = barrier.image;
                memory.subresourceRange        = barrier.subresourceRange;
                memory.oldLayout               = barrier.oldLayout;
                memory.newLayout               = barrier.newLayout;
		
                device.vkCmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, memory);
            }*/
            
            VkBufferImageCopy          region{};
            region.bufferOffset      = 0;
            region.bufferRowLength   = 0;
            region.bufferImageHeight = 0;
            region.imageSubresource  = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
            region.imageOffset       = { 0, 0, 0 };
            region.imageExtent       = { swapChain.m_Info.imageExtent.width, swapChain.m_Info.imageExtent.height, 1 };
            
            device.m_Table.CmdCopyImageToBuffer(commandBuffer.Handle(), swapChain.m_Images[*pPresentInfo->pImageIndices], VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, swapChain.m_StagingBuffer->Handle(), 1, &region);
            
            /*{
                VkImageMemoryBarrier             memory{};
                memory.sType                   = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
                memory.srcAccessMask           = ToVkAccessFlags(barrier.srcAccessMask);
                memory.dstAccessMask           = ToVkAccessFlags(barrier.dstAccessMask);
                memory.srcQueueFamilyIndex     = barrier.srcQueueFamilyIndex;
                memory.dstQueueFamilyIndex     = barrier.dstQueueFamilyIndex;
                memory.image                   = barrier.image;
                memory.subresourceRange        = barrier.subresourceRange;
                memory.oldLayout               = barrier.oldLayout;
                memory.newLayout               = barrier.newLayout;
		
                device.vkCmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, memory);
            }*/
        }
        
        {
            device.m_Table.EndCommandBuffer(commandBuffer.Handle());
        }
        
        {
            std::vector<VkPipelineStageFlags> flags(pPresentInfo->waitSemaphoreCount, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
            
            VkSubmitInfo                     info{};
            info.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            info.waitSemaphoreCount        = pPresentInfo->waitSemaphoreCount;
            info.pWaitSemaphores           = pPresentInfo->pWaitSemaphores;
            info.pWaitDstStageMask         = flags.data();
            info.commandBufferCount        = 1;
            info.pCommandBuffers           = &commandBuffer.Handle();
            info.signalSemaphoreCount      = 1;
            info.pSignalSemaphores         = &commandBuffer.Semaphore();
            
            device.m_Table.QueueSubmit(queue, 1, &info, VK_NULL_HANDLE);
        }
        
        VkPresentInfoKHR presentInfo       = *pPresentInfo;
        presentInfo.waitSemaphoreCount     = 1;
        presentInfo.pWaitSemaphores        = &commandBuffer.Semaphore();
        
        auto result = device.m_Table.QueuePresentKHR(queue, &presentInfo);
        
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
        {
            return result;
        }
        
        VULKAN_CHECK(result)
        
        VULKAN_CHECK(device.m_Table.QueueWaitIdle(queue))
        
        auto w = swapChain.m_Info.imageExtent.width;
        auto h = swapChain.m_Info.imageExtent.height;
        
        static uint64_t frameId = 0;
        
        if (frameId++ % 30 == 0)
        {
            if (!SavePng(MakePath("C:/Users/spices/Desktop/save", frameId, w, h), swapChain.m_StagingBuffer->Data(), w, h, Vulkan::ToSize(swapChain.m_Info.imageFormat)))
            {
               NEPTUNE_LOG_CORE(E) << "SwapChain Image Save ad Png Failed.";
            }
        }
        
        return VK_SUCCESS;
    }
}
