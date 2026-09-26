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

        m_Size = desc.size;
        
        m_Handle = wgpuDeviceCreateBuffer(device, &desc);
        
        if (desc.mappedAtCreation)
        {
            m_HostMemory  = wgpuBufferGetMappedRange(m_Handle, 0, desc.size);
        }
    }

    void Buffer::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuBufferSetLabel(m_Handle, { name.c_str(), name.size() });
    }

    void Buffer::WriteToBuffer(const void* data, uint64_t size, uint64_t offset) const
    {
        NEPTUNE_PROFILE_ZONE
        
        size = std::min(m_Size, size);
        
        if (!m_HostMemory)
        {
            NEPTUNE_LOG_CORE(W) << "Buffer Descriptor without mappedAtCreation.";
            return;
        }

        char* memOffset = static_cast<char*>(m_HostMemory);
        memOffset += offset;
        std::memcpy(memOffset, data, size);
    }
}

#endif