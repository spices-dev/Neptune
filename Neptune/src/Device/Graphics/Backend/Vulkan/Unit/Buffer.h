/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

#include <vk_mem_alloc.h>
#include <variant>

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Buffer Class.
	* This class defines the Vulkan::Unit::Buffer behaves.
	*/
	class Buffer : public Unit<VkBuffer, VkObjectType::VK_OBJECT_TYPE_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Buffer() = default;

		/**
		* @brief Destructor Function.
		*/
		~Buffer() override;

		/**
		* @brief Get Buffer size.
		* 
		* @return Returns Buffer size.
		*/
		VkDeviceSize Size() const { return m_Size; }

		/**
		* @brief Get Buffer Host data.
		*
		* @return Returns Buffer Host data.
		*/
		void* HostMemory() const;

		/**
		* @brief Create Buffer.
		*
		* @param[in] physicalDevice VkPhysicalDevice.
		* @param[in] device VkDevice.
		* @param[in] info VkBufferCreateInfo.
		* @param[in] properties VkMemoryPropertyFlags.
		*/
		void CreateBuffer(VkPhysicalDevice physicalDevice, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties);

		/**
		* @brief Create Buffer.
		*
		* @param[in] vma VmaAllocator.
		* @param[in] device VkDevice.
		* @param[in] info VkBufferCreateInfo.
		* @param[in] properties VkMemoryPropertyFlags.
		*/
		void CreateBuffer(VmaAllocator vma, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties);

		/**
		* @brief Write data to Buffer.
		*
		* @param[in] data .
		* @param[in] size VkDeviceSize.
		* @param[in] offset VkDeviceSize.
		*/
		void WriteToBuffer(const void* data, VkDeviceSize size = UINT64_MAX, VkDeviceSize offset = 0);

		/**
		* @brief Flush Buffer data.
		*
		* @param[in] size VkDeviceSize.
		* @param[in] offset VkDeviceSize.
		*/
		void Flush(VkDeviceSize size = UINT64_MAX, VkDeviceSize offset = 0);

		/**
		* @brief Get Buffer Device Address.
		*
		* @return Returns Buffer Device Address.
		*/
		VkDeviceAddress GetDeviceAddress() const { return m_Address; }
		
	private:

		/**
		* @brief vkAlloc
		*/
		struct vkAlloc {
			VkDevice         device     = VK_NULL_HANDLE;
			VkDeviceMemory   memory     = VK_NULL_HANDLE;
			void*            hostMemory = nullptr;
		};

		/**
		* @brief vmaAlloc
		*/
		struct vmaAlloc {
			VmaAllocator   vma        = VK_NULL_HANDLE;
			VmaAllocation  alloc      = VK_NULL_HANDLE;
			void*          hostMemory = nullptr;
		};

		std::variant<std::monostate, vkAlloc, vmaAlloc> m_Alloc{ std::monostate{} };   // @brief Alloc data.
		VkDeviceAddress       m_Address = 0;                                           // @brief Buffer Device Address.
		VkDeviceSize          m_Size    = 0;                                           // @brief Buffer Size.
		VkMemoryPropertyFlags m_Flags   = 0;                                           // @brief Buffer Memory Flags.
	};
}

#endif