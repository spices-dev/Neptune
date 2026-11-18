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
		
		commandBuffer->CmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, { memory });
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
		
		commandBuffer->CmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, { memory });
	}
	
	void Synchronization::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkMemoryBarrier2& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkMemoryBarrier                  memory{};
		memory.sType                   = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
		memory.srcAccessMask           = ToVkAccessFlags(barrier.srcAccessMask);
		memory.dstAccessMask           = ToVkAccessFlags(barrier.dstAccessMask);
		
		commandBuffer->CmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, { memory });
	}
	
	void Synchronization::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const std::vector<VkMemoryBarrier2>& memoryBatch, const std::vector<VkImageMemoryBarrier2>& imageBatch, const std::vector<VkBufferMemoryBarrier2>& bufferBatch) const
	{
		NEPTUNE_PROFILE_ZONE
		
		std::vector<VkMemoryBarrier>       memoryBatch1;
		std::vector<VkImageMemoryBarrier>  imageBatch1;
		std::vector<VkBufferMemoryBarrier> bufferBatch1;
		
		for (const auto& barrier : memoryBatch)
		{
			VkMemoryBarrier                  memory{};
			memory.sType                   = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
			memory.srcAccessMask           = ToVkAccessFlags(barrier.srcAccessMask);
			memory.dstAccessMask           = ToVkAccessFlags(barrier.dstAccessMask);
			
			memoryBatch1.emplace_back(memory);
		}
		
		for (const auto& barrier : imageBatch)
		{
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
			
			imageBatch1.emplace_back(memory);
		}
		
		for (const auto& barrier : bufferBatch)
		{
			VkBufferMemoryBarrier            memory{};
			memory.sType                   = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
			memory.srcAccessMask           = ToVkAccessFlags(barrier.srcAccessMask);
			memory.dstAccessMask           = ToVkAccessFlags(barrier.dstAccessMask);
			memory.srcQueueFamilyIndex     = barrier.srcQueueFamilyIndex;
			memory.dstQueueFamilyIndex     = barrier.dstQueueFamilyIndex;
			memory.buffer                  = barrier.buffer;
			memory.offset                  = barrier.offset;
			memory.size                    = barrier.size;
			
			bufferBatch1.emplace_back(memory);
		}
		
		commandBuffer->CmdPipelineBarrier(VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, 0, memoryBatch1, imageBatch1, bufferBatch1);
	}
}

#endif