/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Buffer.h"

namespace Neptune::Vulkan::Resource {

    VkResult Buffer::CreateBuffer(const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties, const VkAllocationCallbacks* pAllocator)
    {
    	m_Buffer.SetLife({m_DeviceTable->m_Table.CreateBuffer, m_DeviceTable->m_Table.DestroyBuffer, pAllocator });
    	
        VULKAN_CHECK(m_Buffer.CreateBuffer(m_DeviceTable->Handle(), info))
        
        VkMemoryDedicatedRequirements                       dedicatedRegs{};
		dedicatedRegs.sType                               = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS;

		VkMemoryRequirements2                               memReqs{};
		memReqs.sType                                     = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
		memReqs.pNext                                     = &dedicatedRegs;

		VkBufferMemoryRequirementsInfo2                     bufferReqs{};
		bufferReqs.sType                                  = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
		bufferReqs.buffer                                 = Handle();

		m_DeviceTable->m_Table.GetBufferMemoryRequirements2(m_DeviceTable->Handle(), &bufferReqs, &memReqs);

		VkMemoryAllocateInfo                                allocInfo{};
		allocInfo.sType                                   = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize                          = memReqs.memoryRequirements.size;

		VkMemoryAllocateFlagsInfoKHR                        flagsInfo{};
		flagsInfo.sType                                   = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR;
		flagsInfo.flags                                   = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT;

		if (info.usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)
		{
			allocInfo.pNext = &flagsInfo;
		}

		VkPhysicalDeviceMemoryProperties memProperties{};
		m_InstanceTable->m_Table.GetPhysicalDeviceMemoryProperties(m_DeviceTable->vkPhysicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if (memReqs.memoryRequirements.memoryTypeBits & (1 << i) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				allocInfo.memoryTypeIndex = i;
				break;
			}
		}

    	VULKAN_CHECK(m_DeviceTable->m_Table.AllocateMemory(m_DeviceTable->Handle(), &allocInfo, pAllocator, &m_DeviceMemory))
		
		VULKAN_CHECK(m_DeviceTable->m_Table.BindBufferMemory(m_DeviceTable->Handle(), Handle(), m_DeviceMemory, 0))

		if (info.usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)
		{
			VkBufferDeviceAddressInfo           info{};
			info.sType                        = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
			info.buffer                       = Handle();

			m_Address = m_DeviceTable->m_Table.GetBufferDeviceAddress(m_DeviceTable->Handle(), &info);
		}

		if (properties & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			VULKAN_CHECK(m_DeviceTable->m_Table.MapMemory(m_DeviceTable->Handle(), m_DeviceMemory, 0, info.size, 0, &m_HostMemory))
		}
    	
    	m_Size  = info.size;
    	m_Flags = properties;
    	
    	return VK_SUCCESS;
    }

    void Buffer::WriteToBuffer(const void* data, VkDeviceSize size, VkDeviceSize offset) const
    {
    	size = std::min(m_Size, size);
    	
    	if (!m_HostMemory)
    	{
    		NEPTUNE_LOG_CORE(W) << "Vulkan::Resource::Buffer Property without VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT.";
    		return;
    	}

    	char* memOffset = static_cast<char*>(m_HostMemory);
    	memOffset += offset;
    	std::memcpy(memOffset, data, size);
    }

    VkResult Buffer::Flush(VkDeviceSize size, VkDeviceSize offset) const
    {
    	size = std::min(m_Size, size);
    	
    	VkMappedMemoryRange                  range{};
    	range.sType                        = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    	range.memory                       = m_DeviceMemory;
    	range.offset                       = offset;
    	range.size                         = size;
    	
    	return m_DeviceTable->m_Table.FlushMappedMemoryRanges(m_DeviceTable->Handle(), 1, &range);
    }
    
}