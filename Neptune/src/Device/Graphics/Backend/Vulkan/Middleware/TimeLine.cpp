/**
* @file TimeLine.cpp.
* @brief The TimeLine Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "TimeLine.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"

namespace Neptune::Vulkan::Middleware {
	
	TimeLine::TimeLine(Context& context, uint32_t count)
		: ContextAccessor(context)
	{
		NEPTUNE_PROFILE_ZONE
		
		Create(count);
	}

	void TimeLine::Wait(uint64_t frameId) const
	{
		NEPTUNE_PROFILE_ZONE
		
		auto& fence = m_Fences[frameId % m_Fences.size()];

		fence->Wait();

		fence->ResetFence();
	}

	void TimeLine::Create(uint32_t count)
	{
		NEPTUNE_PROFILE_ZONE
		
		VkFenceCreateInfo             fenceInfo{};
		fenceInfo.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags             = VK_FENCE_CREATE_SIGNALED_BIT;

		for (uint32_t i = 0; i < count; ++i)
		{
			auto fence = CreateUP<Unit::Fence>();

			fence->CreateFence(GetContext().Get<IDevice>()->Handle(), fenceInfo);
 
			fence->ResetFence();

			DEBUGUTILS_SETOBJECTNAME(*fence, "TimeLineFence")

			m_Fences.emplace_back(std::move(fence));
		}
		
		VkSemaphoreCreateInfo              semaphoreInfo {};
		semaphoreInfo.sType              = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		
		for (uint32_t i = 0; i < count; ++i)
		{
			auto semaphore = CreateUP<Unit::Semaphore>();

			semaphore->CreateSemaphore(GetContext().Get<IDevice>()->Handle(), semaphoreInfo);

			DEBUGUTILS_SETOBJECTNAME(*semaphore, "TimeLineBinarySemaphore")

			m_Semaphores.emplace_back(std::move(semaphore));
		}
	}
	
	VkSemaphore TimeLine::Semaphore(uint64_t frameId) const
	{
		NEPTUNE_PROFILE_ZONE
		
		return m_Semaphores[frameId % m_Fences.size()]->GetHandle();
	}
	
	VkFence TimeLine::Fence(uint64_t frameId) const
	{
		NEPTUNE_PROFILE_ZONE
		
		return m_Fences[frameId % m_Fences.size()]->GetHandle();
	}
	
	void TimeLine::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE
		
		for (uint32_t i = 0; i < m_Fences.size(); ++i)
		{
			DEBUGUTILS_SETOBJECTNAME(*m_Fences[i], name + "Fence")
			
			DEBUGUTILS_SETOBJECTNAME(*m_Semaphores[i], name + "BinarySemaphore")
		}
	}
}

#endif