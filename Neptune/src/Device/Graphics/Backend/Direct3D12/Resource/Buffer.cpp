/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Buffer.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Direct3D12::Resource {

	void Buffer::CreateBuffer(const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES state, D3D12_HEAP_TYPE type)
	{
		NEPTUNE_PROFILE_ZONE

		m_Size = desc.Width;
		
		m_Buffer.CreateCommittedResource(GetContext().Get<IDevice>()->Handle(), desc, state, type);
		
		DEBUGUTILS_SETOBJECTNAME(m_Buffer, "Buffer")
	}

	void Buffer::WriteToBuffer(const void* data, uint64_t size, uint64_t offset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		char* memOffset = static_cast<char*>(m_HostMemory);
		memOffset += offset;

		std::memcpy(memOffset, data, size);
	}

	void Buffer::MapHostMemory()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Buffer.GetHandle()->Map(0, nullptr, &m_HostMemory);
	}

	void Buffer::UnapHostMemory()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Buffer.GetHandle()->Unmap(0, nullptr);
		
		m_HostMemory = nullptr;
	}
	
	D3D12_GPU_VIRTUAL_ADDRESS Buffer::GetDeviceAddress() const
	{
		NEPTUNE_PROFILE_ZONE
		
		return m_Buffer.GetHandle()->GetGPUVirtualAddress();
	}
	
	void Buffer::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Buffer, name)
	}
}

#endif