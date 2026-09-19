/**
* @file ITimeLine.h.
* @brief The ITimeLine Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"

namespace Neptune::Vulkan::Middleware {
	
	/**
	* @brief ITimeLine of RenderPass.
	*/
	class ITimeLine
	{
	public:

		/**
		* @brief Create ITimeLine.
		* 
		* @param context Context.
		* @param[in] count Flight Frame Count.
		* 
		* @return Returns ITimeLine.
		*/
		static UP<ITimeLine> Create(Context& context, uint32_t count);
		
		/**
		* @brief Destructor Function.
		*/
		virtual ~ITimeLine() = default;
		
		/**
		* @brief Interface of Wait TimeLine.
		* 
		* @param[in] frameId Frame Id;
		*/
		virtual void Wait(uint64_t frameId) const = 0;
		
		/**
		* @brief Interface of Get Semaphore.
		* 
		* @param[in] frameId Frame Id;
		* 
		* @return Returns VkSemaphore.
		*/
		virtual VkSemaphore Semaphore(uint64_t frameId) const = 0;
        
		/**
		* @brief Interface of Get Fence.
		* 
		* @param[in] frameId Frame Id;
		* 
		* @return Returns VkFence.
		*/
		virtual VkFence Fence(uint64_t frameId) const = 0;
		
		/**
		* @brief Set Name.
		* 
		* @param[in] name .
		*/
		virtual void SetName(const std::string& name) const = 0;
	};
}

#endif