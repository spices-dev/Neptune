/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Buffer.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Vulkan::Resource {

	void Buffer::CreateBuffer(const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		NEPTUNE_PROFILE_ZONE

		GetContext().Has<IMemoryAllocator>() ? 
		m_Buffer.CreateBuffer(GetContext().Get<IMemoryAllocator>()->Handle(), GetContext().Get<IDevice>()->Handle(), info, properties) : 
		m_Buffer.CreateBuffer(GetContext().Get<IPhysicalDevice>()->Handle(), GetContext().Get<IDevice>()->Handle(), info, properties);
	}

	void Buffer::WriteToBuffer(const void* data, VkDeviceSize size, VkDeviceSize offset)
	{
		NEPTUNE_PROFILE_ZONE

		m_Buffer.WriteToBuffer(data, size, offset);
	}

	void Buffer::Flush(VkDeviceSize size, VkDeviceSize offset)
	{
		NEPTUNE_PROFILE_ZONE

		m_Buffer.Flush(size, offset);
	}
	
	VkDeviceAddress Buffer::GetDeviceAddress() const
	{
		NEPTUNE_PROFILE_ZONE
		
		return m_Buffer.GetDeviceAddress();
	}

	void Buffer::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Buffer, name)
	}
}

#endif