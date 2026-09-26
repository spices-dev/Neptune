/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Buffer.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Future.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Instance.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"

namespace Neptune::WebGPU::Resource {

	void Buffer::CreateBuffer(const WGPUBufferDescriptor& desc)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Buffer.CreateBuffer(GetContext().Get<IDevice>()->Handle(), desc);
		
		DEBUGUTILS_SETOBJECTNAME(m_Buffer, "Buffer")
	}

	void Buffer::WriteToBuffer(const void* data, uint64_t size, uint64_t offset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Buffer.WriteToBuffer(data, size, offset);
	}

	void Buffer::MapHostMemory()
	{
		NEPTUNE_PROFILE_ZONE
		
		Unit::Future future;
        
		future.SetHandle(m_Buffer.MapHostMemory());
        
		future.Wait(GetContext().Get<IInstance>()->Handle());
	}

	void Buffer::UnapHostMemory() const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Buffer.UnapHostMemory();
	}

	void Buffer::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Buffer, name)
	}
}

#endif