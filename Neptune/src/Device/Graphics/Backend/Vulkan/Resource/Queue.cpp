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

    void Queue::CreateQueue(Unit::Queue::Handle queue)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Queue.SetHandle(queue);
        
        m_Semaphore.CreateSemaphore();

        DEBUGUTILS_SETOBJECTNAME(m_Queue, "Queue")
    }
	
    void Queue::Submit(const VkSubmitInfo& info) const
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Queue.Submit(info);
    }
    
    void Queue::Submit2(VkCommandBuffer commandBuffer) const
    {
        NEPTUNE_PROFILE_ZONE
		
		VkSemaphoreSubmitInfo                  signalInfo{};
		signalInfo.sType                     = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
		signalInfo.stageMask                 = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
		signalInfo.semaphore                 = m_Semaphore.Handle();
		signalInfo.value                     = m_Semaphore.Next();
    	
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

		m_Queue.Submit2(submitInfo);
    }
	
	void Queue::WaitQueue() const
	{
    	NEPTUNE_PROFILE_ZONE
    	
    	m_Queue.Wait();
    }
	
	void Queue::WaitSemaphore()
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	m_Semaphore.Wait();
    }
	
	void Queue::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE

        DEBUGUTILS_SETOBJECTNAME(m_Queue, name)

        m_Semaphore.SetName(name +"Semaphore");
    }
}

#endif