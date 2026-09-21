/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include <volk.h>

namespace Neptune::Vulkan {

    /**
     * @brief Get Allocator.
     * 
     * @return Returns Allocator. 
     */
    const VkAllocationCallbacks* GetAllocator();
	
    /**
    * @brief Allocate Vulkan Device Memory.
    * 
    * @param[in] device VkDevice.
    * @param[in] pAllocateInfo VkMemoryAllocateInfo.
    * @param[in] pAllocator VkAllocationCallbacks.
    * @param[in] pMemory VkDeviceMemory.
    * @param[in] flags VkMemoryPropertyFlags.
    * 
    * @note VK_EXT_device_memory_report is not supported yet, otherwise we can use it.
    */
    void AllocateMemory(
		VkDevice                          device,
		const VkMemoryAllocateInfo*       pAllocateInfo,
		const VkAllocationCallbacks*      pAllocator,
		VkDeviceMemory*                   pMemory,
		VkMemoryPropertyFlags             flags
	);
	
	/**
	* @brief Free Vulkan Device Memory.
	* 
	* @param[in] device VkDevice.
	* @param[in] memory VkDeviceMemory.
	* @param[in] pAllocator VkAllocationCallbacks.
	* @param[in] flags VkMemoryPropertyFlags.
	*/
	void FreeMemory(
		VkDevice                          device,
		VkDeviceMemory                    memory,
		const VkAllocationCallbacks*      pAllocator,
		VkMemoryPropertyFlags             flags
	);
}

#endif