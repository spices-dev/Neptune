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
		
		commandBuffer->CmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, { ToVkImageMemoryBarrier(barrier) });
	}
	
	void Synchronization::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkBufferMemoryBarrier2& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		commandBuffer->CmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, { ToVkBufferMemoryBarrier(barrier) });
	}
	
	void Synchronization::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkMemoryBarrier2& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		commandBuffer->CmdPipelineBarrier(ToVkPipelineStageFlags(barrier.srcStageMask), ToVkPipelineStageFlags(barrier.dstStageMask), 0, { ToVkMemoryBarrier(barrier) });
	}
	
	void Synchronization::InsertBarrier(const Unit::CommandBuffer* commandBuffer, const std::vector<VkMemoryBarrier2>& memoryBatch, const std::vector<VkImageMemoryBarrier2>& imageBatch, const std::vector<VkBufferMemoryBarrier2>& bufferBatch) const
	{
		NEPTUNE_PROFILE_ZONE
		
		std::vector<VkMemoryBarrier>       memoryBatch1;
		std::vector<VkImageMemoryBarrier>  imageBatch1;
		std::vector<VkBufferMemoryBarrier> bufferBatch1;
		
		memoryBatch1.reserve(memoryBatch.size());
		imageBatch1.reserve(imageBatch.size());
		bufferBatch1.reserve(bufferBatch.size());
		
		for (const auto& barrier : memoryBatch)
		{
			memoryBatch1.emplace_back(ToVkMemoryBarrier(barrier));
		}
		
		for (const auto& barrier : imageBatch)
		{
			imageBatch1.emplace_back(ToVkImageMemoryBarrier(barrier));
		}
		
		for (const auto& barrier : bufferBatch)
		{
			bufferBatch1.emplace_back(ToVkBufferMemoryBarrier(barrier));
		}
		
		commandBuffer->CmdPipelineBarrier(VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, 0, memoryBatch1, imageBatch1, bufferBatch1);
	}
}

#endif