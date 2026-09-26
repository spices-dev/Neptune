/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

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

    WGPUFuture Buffer::MapHostMemory()
    {
        NEPTUNE_PROFILE_ZONE

        struct Payload
        {
            void** hostMemoty;
            Handle handle;
            uint64_t size;
        };
        
        Payload payload { &m_HostMemory, GetHandle(), m_Size };
        
        WGPUBufferMapCallbackInfo        callbackInfo{};
        callbackInfo.mode               = WGPUCallbackMode_WaitAnyOnly;
        callbackInfo.userdata1          = &payload;
        callbackInfo.callback        = [](WGPUMapAsyncStatus status, WGPUStringView message, void* userdata1, void*)
        {
            if (auto p = static_cast<Payload*>(userdata1))
            {
                *(p->hostMemoty) = wgpuBufferGetMappedRange(p->handle, 0, p->size);
            }
        };
        
        return wgpuBufferMapAsync(m_Handle, WGPUMapMode_Write, 0, m_Size, callbackInfo);
    }

    void Buffer::UnapHostMemory() const
    {
        NEPTUNE_PROFILE_ZONE
        
        wgpuBufferUnmap(m_Handle);
    }
}

#endif