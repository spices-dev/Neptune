/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Memory.h"
#include "Core.h"
#include "Core/Memory/Enum.h"

namespace Neptune::Vulkan {

	namespace {
		
		VkAllocationCallbacks s_Allocator;        // @brief VkAllocationCallbacks.

	}

	const VkAllocationCallbacks* GetAllocator()
	{
		NEPTUNE_PROFILE_ZONE
		
#ifdef NEPTUNE_RELEASE
		
		return nullptr;
		
#else
		
		if (!s_Allocator.pfnAllocation)
		{
			s_Allocator.pfnAllocation = +[](void* pUserData, size_t size, size_t alignment, VkSystemAllocationScope allocationScope) -> void* {
				
#ifdef NP_PLATFORM_WINDOWS
				auto* p = _aligned_malloc(size, alignment);
#else
				auto* p = aligned_alloc(alignment, size);
#endif
				
				NEPTUNE_PROFILE_ALLOC_N(p, size, ToString(MemoryEnum::Host))
				
				return p;
			};
		}
		
		if (!s_Allocator.pfnFree)
		{
			s_Allocator.pfnFree = +[](void* pUserData, void* pMemory) -> void {
				
				NEPTUNE_PROFILE_FREE_N(pMemory, ToString(MemoryEnum::Host))
				
#ifdef NP_PLATFORM_WINDOWS
				_aligned_free(pMemory);
#else
				free(pMemory);
#endif
			};
		}

		if (!s_Allocator.pfnReallocation)
		{
			s_Allocator.pfnReallocation = +[](void* pUserData, void* pOriginal, size_t size, size_t alignment, VkSystemAllocationScope scope) -> void* {

					if (pOriginal == nullptr && size > 0) 
					{
#ifdef NP_PLATFORM_WINDOWS
						auto* p = _aligned_malloc(size, alignment);
#else
						auto* p = aligned_alloc(alignment, size);
#endif

						NEPTUNE_PROFILE_ALLOC_N(p, size, ToString(MemoryEnum::Host))

						return p;
					}
					if (size == 0 && pOriginal != nullptr) 
					{
#ifdef NP_PLATFORM_WINDOWS
						_aligned_free(pOriginal);
#else
						free(pOriginal);
#endif
						return nullptr;
					}
					if (pOriginal != nullptr && size > 0) 
					{
#ifdef NP_PLATFORM_WINDOWS
						auto* p = _aligned_realloc(pOriginal, size, alignment);
#else
						auto* p = aligned_alloc(alignment, size);

						free(pOriginal);
#endif

						if (p && p != pOriginal)
						{
							NEPTUNE_PROFILE_FREE_N(pOriginal, ToString(MemoryEnum::Host))

							NEPTUNE_PROFILE_ALLOC_N(p, size, ToString(MemoryEnum::Host))
						}

						return p;
					}

					return nullptr;
				};
		}
		
		return &s_Allocator;
		
#endif
		
	}
	
	void AllocateMemory(
		VkDevice                          device,
		const VkMemoryAllocateInfo*       pAllocateInfo,
		const VkAllocationCallbacks*      pAllocator,
		VkDeviceMemory*                   pMemory,
		VkMemoryPropertyFlags             flags
	) {
		NEPTUNE_PROFILE_ZONE

#ifdef NEPTUNE_RELEASE
		
		VK_CHECK(vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory))
		
#else
		
		auto type = MemoryEnum::Other;
			
		if (flags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) 
		{
			if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) 
			{
				type = MemoryEnum::Shared;
			} 
			else 
			{
				type = MemoryEnum::Device;
			}
		}
		else if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) 
		{
			type = MemoryEnum::HostDevice;
		}
		else 
		{
			type = MemoryEnum::Other;
		}

		VK_CHECK(vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory))
		
		NEPTUNE_PROFILE_ALLOC_N(*pMemory, pAllocateInfo->allocationSize, ToString(type))
		
#endif
		
	}
	
	void FreeMemory(
		VkDevice                          device,
		VkDeviceMemory                    memory,
		const VkAllocationCallbacks*      pAllocator,
		VkMemoryPropertyFlags             flags
	) {
		NEPTUNE_PROFILE_ZONE
		
#ifdef NEPTUNE_DEBUG
		
		auto type = MemoryEnum::Other;
			
		if (flags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) 
		{
			if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) 
			{
				type = MemoryEnum::Shared;
			} 
			else 
			{
				type = MemoryEnum::Device;
			}
		}
		else if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) 
		{
			type = MemoryEnum::HostDevice;
		}
		else 
		{
			type = MemoryEnum::Other;
		}
		
		NEPTUNE_PROFILE_FREE_N(memory, ToString(type))
		
#endif
		
		vkFreeMemory(device, memory, pAllocator);
		
	}
	
}

#endif