/**
* @file Synchronization.h.
* @brief The Synchronization Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "ISynchronization.h"

namespace Neptune::Vulkan::Middleware {
	
	/**
	* @brief Implement of Synchronization.
	*/
	class Synchronization : public ISynchronization
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Synchronization() = default;

		/**
		* @brief Destructor Function.
		*/
		~Synchronization() override = default;

		/**
		* @brief Interface of Insert Image Barrier.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] barrier VkImageMemoryBarrier2.
		*/
		void InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkImageMemoryBarrier2& barrier) const override;
		
		/**
		* @brief Interface of Insert Buffer Barrier.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] barrier VkBufferMemoryBarrier2.
		*/
		void InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkBufferMemoryBarrier2& barrier) const override;
		
		/**
		* @brief Interface of Insert Memory Barrier.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] barrier VkMemoryBarrier2.
		*/
		void InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkMemoryBarrier2& barrier) const override;
		
		/**
		* @brief Interface of Insert Batch Barrier.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] memoryBatch VkMemoryBarrier2.
		* @param[in] imageBatch VkImageMemoryBarrier2.
		* @param[in] bufferBatch VkBufferMemoryBarrier2.
		*/
		void InsertBarrier(const Unit::CommandBuffer* commandBuffer, const std::vector<VkMemoryBarrier2>& memoryBatch, const std::vector<VkImageMemoryBarrier2>& imageBatch, const std::vector<VkBufferMemoryBarrier2>& bufferBatch) const override;
	};
}

#endif