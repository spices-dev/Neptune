/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Vulkan/Infrastructure/DeviceTable.h"
#include "Vulkan/Infrastructure/InstanceTable.h"
#include "Vulkan/Unit/Buffer.h"

namespace Neptune::Vulkan::Resource {

	/**
	* @brief Vulkan::Buffer Class.
	* This class defines the Vulkan::Buffer behaves.
	*/
	class Buffer
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] instance InstanceTable.
		* @param[in] deivce DeviceTable.
		*/
		explicit Buffer(const InstanceTable& instance, const DeviceTable& deivce) : m_InstanceTable(&instance), m_DeviceTable(&deivce) {}

		/**
		* @brief Destructor Function.
		*/
		virtual ~Buffer() = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Buffer::Handle& Handle() const { return m_Buffer.GetHandle(); }

		/**
		* @brief Get Buffer Size.
		*
		* @return Returns Buffer Size.
		*/
		VkDeviceSize Size() const { return m_Size; }

		/**
		* @brief Get Buffer Host Data.
		*
		* @return Returns Buffer Host Data.
		*/
		void* Data() const { return m_HostMemory; }

		/**
		* @brief Create Buffer.
		*
		* @param[in] info VkBufferCreateInfo.
		* @param[in] properties VkMemoryPropertyFlags.
		* @param[in] pAllocator VkAllocationCallbacks.
		* 
		* @return Returns VkResult.
		*/
		VkResult CreateBuffer(const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties, const VkAllocationCallbacks* pAllocator);

		/**
		* @brief Write host data to Buffer.
		*
		* @param[in] data Host data.
		* @param[in] size Buffer size.
		* @param[in] offset Buffer offset.
		*/
		void WriteToBuffer(const void* data, VkDeviceSize size = UINT64_MAX, VkDeviceSize offset = 0) const;

		/**
		* @brief Flush Buffer data.
		*
		* @param[in] size Buffer size.
		* @param[in] offset Buffer offset.
		* 
		* @return Returns VkResult.
		*/
		VkResult Flush(VkDeviceSize size = UINT64_MAX, VkDeviceSize offset = 0) const;

		/**
		* @brief Get Buffer Device Address.
		*
		* @return Returns Buffer Device Address.
		*/
		VkDeviceAddress GetDeviceAddress() const { return m_Address; }

	private:

		const InstanceTable*  m_InstanceTable;              // @brief InstanceTable.
		const DeviceTable*    m_DeviceTable;                // @brief DeviceTable.
		Unit::Buffer          m_Buffer;                     // @brief This Buffer.
		uint64_t              m_Size         = 0;           // @brief Buffer Size.
		void*                 m_HostMemory   = nullptr;     // @brief Buffer Host Memory.
		VkDeviceMemory        m_DeviceMemory = nullptr;     // @brief Buffer Device Memory.
		VkDeviceAddress       m_Address      = 0;           // @brief Buffer Device Address.
		VkMemoryPropertyFlags m_Flags        = 0;           // @brief Buffer Memory Flags.
	};
}