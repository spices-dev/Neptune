/**
* @file Image.cpp.
* @brief The Image Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Image.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/MemoryAllocator.h"

namespace Neptune::Vulkan::Unit {

	Image::~Image()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		if (auto* p = std::get_if<vkAlloc>(&m_Alloc))
		{
			vkDestroyImage(p->device, m_Handle, GetAllocator());

			if (p->memory)
			{
				FreeMemory(p->device, p->memory, GetAllocator(), m_Flags);
			}
		}
		else if (auto* p = std::get_if<vmaAlloc>(&m_Alloc))
		{
			vmaDestroyImage(p->vma, m_Handle, p->alloc);
		}
		else if (auto* p = std::get_if<std::monostate>(&m_Alloc))
		{
			return;
		}
	}

	void Image::CreateImage(VkPhysicalDevice physicalDevice, VkDevice device, const VkImageCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(device)

		vkAlloc alloc{};
		alloc.device = device;

		m_Flags = properties;
		
		VULKAN_CHECK(vkCreateImage(device, &info, GetAllocator(), &m_Handle))

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(device, m_Handle, &memRequirements);

		VkMemoryAllocateInfo           allocInfo{};
		allocInfo.sType              = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize     = memRequirements.size;

		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

		allocInfo.memoryTypeIndex = 0;
		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if (memRequirements.memoryTypeBits & (1 << i) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				allocInfo.memoryTypeIndex = i;
			}
		}

		AllocateMemory(device, &allocInfo, GetAllocator(), &alloc.memory, properties);

		VULKAN_CHECK(vkBindImageMemory(device, m_Handle, alloc.memory, 0))

		m_Alloc = alloc;
	}

	void Image::CreateImage(VmaAllocator vma, const VkImageCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(vma)

		vmaAlloc alloc{};
		alloc.vma = vma;

		m_Flags = properties;
		
		VmaAllocationCreateInfo        allocInfo{};
		allocInfo.usage              = VMA_MEMORY_USAGE_AUTO;

		if (properties & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			allocInfo.flags |= VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
		}

		if (properties & VMA_MEMORY_PROPERTY_DEDICATED_MEMORY_BIT)
		{
			allocInfo.flags |= VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
		}

		VULKAN_CHECK(vmaCreateImage(vma, &info, &allocInfo, &m_Handle, &alloc.alloc, nullptr))

		m_Alloc = alloc;
	}

}

#endif