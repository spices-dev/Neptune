/**
* @file Synchronization2.h.
* @brief The Synchronization2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "ISynchronization.h"

namespace Neptune::Vulkan::Middleware {
	
	/**
	* @brief Implement of Synchronization2.
	*/
	class Synchronization2 : public ISynchronization
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Synchronization2() = default;

		/**
		* @brief Destructor Function.
		*/
		~Synchronization2() override = default;

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
	};
}

#endif