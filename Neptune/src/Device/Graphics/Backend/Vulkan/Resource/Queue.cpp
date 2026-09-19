/**
* @file TimelineSemaphore.cpp.
* @brief The TimelineSemaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Queue.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Vulkan::Resource {
	
	Queue::Queue(Context& context)
		: ContextAccessor(context)
		, m_TimeLine(Middleware::ITimeLine::Create(context, 1))
		, m_QueueSubmit(Middleware::IQueueSubmit::Create(context))
	{}

    void Queue::CreateQueue(Unit::Queue::Handle queue)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Queue.SetHandle(queue);

        DEBUGUTILS_SETOBJECTNAME(m_Queue, "Queue")
    }

    void Queue::Submit(VkCommandBuffer commandBuffer)
    {
        NEPTUNE_PROFILE_ZONE
		
		++m_Time;
		
		VkSemaphoreSubmitInfo                  signalInfo{};
		signalInfo.sType                     = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
		signalInfo.stageMask                 = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
		signalInfo.semaphore                 = m_TimeLine->Semaphore();
		signalInfo.value                     = m_Time;
    	
		VkCommandBufferSubmitInfo              commandInfo{};
		commandInfo.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
		commandInfo.commandBuffer            = commandBuffer;

		VkSubmitInfo2                          submitInfo{};
		submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
		submitInfo.waitSemaphoreInfoCount    = 0;
		submitInfo.pWaitSemaphoreInfos       = nullptr;
		submitInfo.commandBufferInfoCount    = 1;
		submitInfo.pCommandBufferInfos       = &commandInfo;
		submitInfo.signalSemaphoreInfoCount  = 1;
		submitInfo.pSignalSemaphoreInfos     = &signalInfo;

		m_QueueSubmit->Submit(&m_Queue, submitInfo, m_TimeLine->Fence(m_Time));
    }
	
	void Queue::WaitTimeLine() const
	{
    	NEPTUNE_PROFILE_ZONE
    	
		m_TimeLine->Wait(m_Time);
    }
	
	void Queue::Wait() const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Queue.Wait();
	}
	
	void Queue::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE

        DEBUGUTILS_SETOBJECTNAME(m_Queue, name)

        m_TimeLine->SetName(name);
    }
}

#endif