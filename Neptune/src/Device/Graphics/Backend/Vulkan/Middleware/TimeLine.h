/**
* @file TimeLine.h.
* @brief The TimeLine Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Fence.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Semaphore.h"
#include "ITimeLine.h"

namespace Neptune::Vulkan::Middleware {
	
	/**
	* @brief Implement of Classic Fence Semaphore.
	*/
	class TimeLine : public ContextAccessor, public ITimeLine
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] count Fence Count.
		*/
		explicit TimeLine(Context& context, uint32_t count);

		/**
		* @brief Destructor Function.
		*/
		~TimeLine() override = default;
		
		/**
		* @brief Interface of Wait TimeLine.
		* 
		* @param[in] frameId Frame Id;
		*/
		void Wait(uint64_t frameId) const override;
		
		/**
		* @brief Interface of Get Semaphore.
		* 
		* @param[in] frameId Frame Id;
		* 
		* @return Returns VkSemaphore.
		*/
		VkSemaphore Semaphore(uint64_t frameId) const override;
        
		/**
		* @brief Interface of Get Fence.
		* 
		* @param[in] frameId Frame Id;
		* 
		* @return Returns VkFence.
		*/
		VkFence Fence(uint64_t frameId) const override;
		
		/**
		* @brief Set Name.
		* 
		* @param[in] name .
		*/
		void SetName(const std::string& name) const override;
		
	private:
		
		/**
		* @brief Create Fence.
		* 
		* @param[in] count Fence Count.
		*/
		void Create(uint32_t count);
		
	private:
		
		std::vector<UP<Unit::Fence>> m_Fences;                // @brief Container of this Fence.
		std::vector<UP<Unit::Semaphore>> m_Semaphores;        // @brief Container of this Semaphore.
		
	};
}

#endif