/**
* @file Synchronization2.cpp.
* @brief The Synchronization2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Synchronization2.h"
#include "Device/Graphics/Backend/Vulkan/Unit/CommandBuffer.h"

namespace Neptune::Vulkan::Middleware {
	
	void Synchronization2::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkImageMemoryBarrier2& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
				
		VkDependencyInfo                          info{};
		info.sType                              = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
		info.imageMemoryBarrierCount            = 1;
		info.pImageMemoryBarriers               = &barrier;
		
		commandBuffer->CmdPipelineBarrier2(info);
	}
	
	void Synchronization2::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkBufferMemoryBarrier2& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkDependencyInfo                          info{};
		info.sType                              = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
		info.bufferMemoryBarrierCount           = 1;
		info.pBufferMemoryBarriers              = &barrier;
		
		commandBuffer->CmdPipelineBarrier2(info);
	}
	
	void Synchronization2::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkMemoryBarrier2& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkDependencyInfo                          info{};
		info.sType                              = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
		info.memoryBarrierCount                 = 1;
		info.pMemoryBarriers                    = &barrier;
		
		commandBuffer->CmdPipelineBarrier2(info);
	}
}

#endif