/**
* @file MemoryAllocator.cpp.
* @brief The MemoryAllocator Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#define VMA_IMPLEMENTATION

#include "MemoryAllocator.h"
#include "Instance.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/BufferDeviceAddress.h"
#include "Core/Memory/Enum.h"

namespace Neptune::Vulkan {

	namespace {
		
		/**
		* @brief vmaAllocateDeviceMemoryFunction Callback on AllocMemory.
		* 
		* @param[in] allocator VmaAllocator.
		* @param[in] memoryType VkPhysicalDeviceMemoryProperties::memoryTypes
		* @param[in] memory VkDeviceMemory.
		* @param[in] size VkDeviceSize.
		* @param[in] pUserData MemoryAllocator.
		*/
		void vmaAllocateDeviceMemoryFunction(
			VmaAllocator      allocator,
			uint32_t          memoryType,
			VkDeviceMemory    memory,
			VkDeviceSize      size,
			void*             pUserData
		){
			auto self = static_cast<MemoryAllocator*>(pUserData);
			
			auto flags = self->GetProps().memoryTypes[memoryType].propertyFlags;
			
			auto type = EMemory::Other;
			
			if (flags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) 
			{
				if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) 
				{
					type = EMemory::Shared;
				} 
				else 
				{
					type = EMemory::Device;
				}
			}
			else if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) 
			{
				type = EMemory::HostDevice;
			}
			else 
			{
				type = EMemory::Other;
			}
			
			NEPTUNE_PROFILE_ALLOC_N(memory, size, ToString(type))
		}
		
		/**
		* @brief vmaFreeDeviceMemoryFunction Callback on FreeMemory.
		* 
		* @param[in] allocator VmaAllocator.
		* @param[in] memoryType VkPhysicalDeviceMemoryProperties::memoryTypes
		* @param[in] memory VkDeviceMemory.
		* @param[in] size VkDeviceSize.
		* @param[in] pUserData MemoryAllocator.
		*/
		void vmaFreeDeviceMemoryFunction(
			VmaAllocator      allocator,
			uint32_t          memoryType,
			VkDeviceMemory    memory,
			VkDeviceSize      size,
			void*             pUserData
		){
			auto self = static_cast<MemoryAllocator*>(pUserData);
			
			auto flags = self->GetProps().memoryTypes[memoryType].propertyFlags;
			
			auto type = EMemory::Other;
			
			if (flags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) 
			{
				if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) 
				{
					type = EMemory::Shared;
				} 
				else 
				{
					type = EMemory::Device;
				}
			}
			else if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) 
			{
				type = EMemory::HostDevice;
			}
			else 
			{
				type = EMemory::Other;
			}
			
			NEPTUNE_PROFILE_FREE_N(memory, ToString(type))
		}
		
	}
	
	MemoryAllocator::MemoryAllocator(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create();
	}

	MemoryAllocator::~MemoryAllocator()
	{
		NEPTUNE_PROFILE_ZONE

		VmaTotalStatistics stats{};

		vmaCalculateStatistics(Handle(), &stats);

		if (stats.total.statistics.allocationCount)
		{
			char* statsString = nullptr;

			vmaBuildStatsString(Handle(), &statsString, true);

			NEPTUNE_LOG_CORE(E) << "VMA Stats: \n" << statsString;

			vmaFreeStatsString(Handle(), statsString);
		}

		vmaDestroyAllocator(Handle());

		m_Handle = nullptr;
	}

	void MemoryAllocator::Create()
	{
		NEPTUNE_PROFILE_ZONE

		// see https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/quick_start.html
		VmaAllocatorCreateInfo                  createInfo {};
		createInfo.instance                   = GetContext().Get<IInstance>()->Handle();
		createInfo.physicalDevice             = GetContext().Get<IPhysicalDevice>()->Handle();
		createInfo.device                     = GetContext().Get<IDevice>()->Handle();
		createInfo.vulkanApiVersion           = VK_VERSION;
		createInfo.flags                      = VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT      | 
												VMA_ALLOCATOR_CREATE_KHR_BIND_MEMORY2_BIT              |
												VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE4_BIT              |
												VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE5_BIT              |
												VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT             |
												VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT           |
												VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT |
												VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT           ;

		if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IBufferDeviceAddress>())
		{
			createInfo.flags                 |= VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
		}
		
#ifdef NEPTUNE_DEBUG
		
		VmaDeviceMemoryCallbacks                deviceMemoryCallbacks{};
		deviceMemoryCallbacks.pfnAllocate     = vmaAllocateDeviceMemoryFunction;
		deviceMemoryCallbacks.pfnFree         = vmaFreeDeviceMemoryFunction;
		deviceMemoryCallbacks.pUserData       = this;
		
		createInfo.pDeviceMemoryCallbacks     = &deviceMemoryCallbacks;
		createInfo.pAllocationCallbacks       = GetAllocator();
		
#endif
		
		VULKAN_CHECK(vmaCreateAllocator(&createInfo, &m_Handle))
		
		vkGetPhysicalDeviceMemoryProperties(GetContext().Get<IPhysicalDevice>()->Handle(), &m_MemProps);
	}
}

#endif