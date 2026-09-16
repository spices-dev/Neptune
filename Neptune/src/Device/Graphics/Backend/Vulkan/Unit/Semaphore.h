/**
* @file Semaphore.h.
* @brief The Semaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Semaphore Class.
	* This class defines the Vulkan::Unit::Semaphore behaves.
	*/
	class Semaphore : public Unit<VkSemaphore, VkObjectType::VK_OBJECT_TYPE_SEMAPHORE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Semaphore() = default;

		/**
		* @brief Destructor Function.
		*/
		~Semaphore() override;

		/**
		* @brief Create Semaphore.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkSemaphoreCreateInfo.
		*/
		void CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& info);

		/**
		* @brief Get Semaphore Value.
		*
		* @return Returns Semaphore Value.
		*/
		uint64_t GetValue() const;
		
		/**
		* @brief Wait Semaphore.
		* 
		* @param[in] value Wait Value;
		*/
		void Wait(uint64_t value) const;
		
		/**
		* @brief Signal Semaphore.
		* 
		* @param[in] value Signal Value;
		*/
		void Signal(uint64_t value) const;
		
	private:

		VkDevice m_Device = VK_NULL_HANDLE;           // @brief VkDevice.
	};
}

#endif