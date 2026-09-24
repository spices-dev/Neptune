/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "Buffer.h"

namespace Neptune::WebGPU::Unit {

    Buffer::~Buffer()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuBufferRelease(m_Handle);
    }

    void Buffer::CreateBuffer(WGPUDevice device, const WGPUBufferDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateBuffer(device, &desc);
    }

    void Buffer::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuBufferSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif