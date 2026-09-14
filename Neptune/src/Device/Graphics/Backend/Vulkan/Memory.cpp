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

		/**
		* @brief Alloc memory with alignment.
		* 
		* @param size Memory size.
		* @param alignment Memory alignment.
		* 
		* @return Return alloc memory.
		*/
		void* AlignedAlloc(size_t size, size_t alignment)
		{
			if (size == 0) return nullptr;
			
#ifdef NP_PLATFORM_WINDOWS
			
			return _aligned_malloc(size, alignment);
			
#else
			
			const size_t align = alignment < sizeof(void*) ? sizeof(void*) : alignment;
			
			void* p = nullptr;
			
			if (posix_memalign(&p, align, size) != 0) return nullptr;
			
			return p;
			
#endif
			
		}
		
		/**
		* @brief Calculate memory alignment size.
		* 
		* @param p Memory pointer.
		* 
		* @return Return alignment size.
		*/
		size_t AlignedSize(void* p)
		{
			
#ifdef NP_PLATFORM_WINDOWS
			
			return _aligned_msize(p, sizeof(void*), 0);
			
#elif defined(NP_PLATFORM_MACOS)
			
			return malloc_size(p);
			
#else
			
			return malloc_usable_size(p);
			
#endif
			
		}

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
				
				auto* p = AlignedAlloc(size, alignment);
				
				NEPTUNE_PROFILE_ALLOC_N(p, size, ToString(EMemory::Host))
				
				return p;
			};
		}
		
		if (!s_Allocator.pfnFree)
		{
			s_Allocator.pfnFree = +[](void* pUserData, void* pMemory) -> void {
				
				NEPTUNE_PROFILE_FREE_N(pMemory, ToString(EMemory::Host))
				
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
						auto* p = AlignedAlloc(size, alignment);

						NEPTUNE_PROFILE_ALLOC_N(p, size, ToString(EMemory::Host))

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
						
						auto* p = AlignedAlloc(size, alignment);
						
						if (p)
						{
							std::memcpy(p, pOriginal, std::min(AlignedSize(pOriginal), size));
							
							free(pOriginal);
						}
						
#endif

						if (p && p != pOriginal)
						{
							NEPTUNE_PROFILE_FREE_N(pOriginal, ToString(EMemory::Host))

							NEPTUNE_PROFILE_ALLOC_N(p, size, ToString(EMemory::Host))
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
		
		VULKAN_CHECK(vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory))
		
#else
		
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

		VULKAN_CHECK(vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory))
		
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
		
#endif
		
		vkFreeMemory(device, memory, pAllocator);
		
	}
	
}

#endif