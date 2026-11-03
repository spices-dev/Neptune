/**
* @file CommandBuffer.h.
* @brief The CommandBuffer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::CommandBuffer Class.
	* This class defines the Vulkan::Unit::CommandBuffer behaves.
	*/
	class CommandBuffer : public Unit<VkCommandBuffer, PFN_vkAllocateCommandBuffers, PFN_vkFreeCommandBuffers>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandBuffer() = default;

		/**
		* @brief Destructor Function.
		*/
		~CommandBuffer() override;

		/**
		* @brief Create CommandBuffer.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkCommandBufferAllocateInfo.
		*/
		void CreateCommandBuffer(VkDevice device, const VkCommandBufferAllocateInfo& info);

	private:

		VkDevice m_Device           = VK_NULL_HANDLE;     // @brief VkDevice.
		VkCommandPool m_CommandPool = VK_NULL_HANDLE;     // @brief VkCommandPool.

	};
}