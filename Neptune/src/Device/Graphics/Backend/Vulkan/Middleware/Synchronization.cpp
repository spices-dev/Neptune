/**
* @file Synchronization.cpp.
* @brief The Synchronization Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Synchronization.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"
#include "Device/Graphics/Backend/Vulkan/Unit/CommandBuffer.h"

namespace Neptune::Vulkan::Middleware {
	
	void Synchronization::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkImageMemoryBarrier2& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
				
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
		
		commandBuffer->CmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, memory);
	}
	
	void Synchronization::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkBufferMemoryBarrier2& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkBufferMemoryBarrier            memory{};
		memory.sType                   = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
		memory.srcAccessMask           = ToVkAccessFlags(barrier.srcAccessMask);
		memory.dstAccessMask           = ToVkAccessFlags(barrier.dstAccessMask);
		memory.srcQueueFamilyIndex     = barrier.srcQueueFamilyIndex;
		memory.dstQueueFamilyIndex     = barrier.dstQueueFamilyIndex;
		memory.buffer                  = barrier.buffer;
		memory.offset                  = barrier.offset;
		memory.size                    = barrier.size;
		
		commandBuffer->CmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, memory);
	}
	
	void Synchronization::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkMemoryBarrier2& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkMemoryBarrier                  memory{};
		memory.sType                   = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
		memory.srcAccessMask           = ToVkAccessFlags(barrier.srcAccessMask);
		memory.dstAccessMask           = ToVkAccessFlags(barrier.dstAccessMask);
		
		commandBuffer->CmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, memory);
	}
}

#endif