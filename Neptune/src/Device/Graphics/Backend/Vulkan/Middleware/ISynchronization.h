/**
* @file ISynchronization.h.
* @brief The ISynchronization Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Unit {
	
	class CommandBuffer;
}

namespace Neptune::Vulkan::Middleware {
	
	using IISynchronization = IMiddleware<class ISynchronization, EMiddleware::Synchronization>;
	
	/**
	* @brief Interface of Synchronization.
	*/
	class ISynchronization : public Middleware
	{
	public:
		
		/**
		* @brief Create ISynchronization.
		* 
		* @param context Context.
		* 
		* @return Returns ISynchronization.
		*/
		static UP<ISynchronization> Create(const Context& context);
		
		/**
		* @brief Destructor Function.
		*/
		~ISynchronization() override = default;

		/**
		* @brief Interface of Insert Image Barrier.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] barrier VkImageMemoryBarrier2.
		*/
		virtual void InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkImageMemoryBarrier2& barrier) const = 0;

		/**
		* @brief Interface of Insert Buffer Barrier.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] barrier VkBufferMemoryBarrier2.
		*/
		virtual void InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkBufferMemoryBarrier2& barrier) const = 0;
		
		/**
		* @brief Interface of Insert Memory Barrier.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] barrier VkMemoryBarrier2.
		*/
		virtual void InsertBarrier(const Unit::CommandBuffer* commandBuffer, const VkMemoryBarrier2& barrier) const = 0;
	};
}

#endif