/**
* @file IQueueSubmit.cpp.
* @brief The IQueueSubmit Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IQueueSubmit.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/TimelineSemaphore.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Queue.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"

namespace Neptune::Vulkan::Middleware {
	
    UP<IQueueSubmit> IQueueSubmit::Create(const Context& context)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (context.Get<IExtensions>()->GetContext()->Has<Extension::ITimelineSemaphore>())
        {
            return CreateUP<QueueSubmit2>();
        }

        return CreateUP<QueueSubmit>();
    }

    void QueueSubmit::Submit(const Unit::Queue* queue, const VkSubmitInfo2& info, VkFence fence) const
    {
        NEPTUNE_PROFILE_ZONE
        
        std::vector<VkSemaphore> wait{};
        
        std::vector<VkPipelineStageFlags> waitStages{};
        {
            for (uint32_t i = 0; i < info.waitSemaphoreInfoCount; ++i)
            {
                wait.emplace_back(info.pWaitSemaphoreInfos[i].semaphore);
                
                waitStages.emplace_back(ToVkPipelineStageFlags(info.pWaitSemaphoreInfos[i].stageMask));
            }
        }
        
        std::vector<VkCommandBuffer> commandBuffer{};
        {
            for (uint32_t i = 0; i < info.commandBufferInfoCount; ++i)
            {
                commandBuffer.emplace_back(info.pCommandBufferInfos[i].commandBuffer);
            }
        }
        
        std::vector<VkSemaphore> signal{};
        {
            for (uint32_t i = 0; i < info.signalSemaphoreInfoCount; ++i)
            {
                signal.emplace_back(info.pSignalSemaphoreInfos[i].semaphore);
            }
        }
        
        VkSubmitInfo                           submitInfo{};
        submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.waitSemaphoreCount        = wait.size();
        submitInfo.pWaitSemaphores           = wait.empty()          ? nullptr : wait.data();
        submitInfo.pWaitDstStageMask         = waitStages.empty()    ? nullptr : waitStages.data();
        submitInfo.commandBufferCount        = commandBuffer.size();
        submitInfo.pCommandBuffers           = commandBuffer.empty() ? nullptr : commandBuffer.data();
        submitInfo.signalSemaphoreCount      = signal.size();
        submitInfo.pSignalSemaphores         = signal.empty()        ? nullptr : signal.data();
        
        queue->Submit(submitInfo, fence);
    }

    void QueueSubmit2::Submit(const Unit::Queue* queue, const VkSubmitInfo2& info, VkFence fence) const
    {
        NEPTUNE_PROFILE_ZONE
        
        queue->Submit2(info, fence);
    }
}

#endif