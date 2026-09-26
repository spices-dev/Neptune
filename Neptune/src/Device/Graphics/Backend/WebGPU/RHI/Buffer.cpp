/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Buffer.h"
#include "Core/Math/Math.h"
#include "CmdList2.h"
#include "Device/Graphics/Backend/WebGPU/Converter.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"

namespace Neptune::WebGPU {
    
    void Buffer::CreateBuffer(uint64_t size, Graphic::EBufferUsage usage)
    {
        NEPTUNE_PROFILE_ZONE
        
        size = AlignUp(size, static_cast<uint64_t>(4));
        
        WGPUBufferDescriptor                  desc{};
        desc.usage                          = WGPUBufferUsage_CopyDst | ToWGPUBufferUsage(usage);
        desc.size                           = size;
        desc.mappedAtCreation               = false;
        
        m_Buffer.CreateBuffer(desc);
    }

    void Buffer::WriteToBuffer(const void* data, uint64_t size)
    {
        NEPTUNE_PROFILE_ZONE
        
        size = AlignUp(size, static_cast<uint64_t>(4));
        
        m_StagingBuffer = CreateUP<Resource::Buffer>();
        
        WGPUBufferDescriptor                  desc{};
        desc.usage                          = WGPUBufferUsage_CopySrc | WGPUBufferUsage_MapWrite;
        desc.size                           = size;
        desc.mappedAtCreation               = true;
    
        m_StagingBuffer->CreateBuffer(desc);

        m_StagingBuffer->WriteToBuffer(data);
    
        m_StagingBuffer->UnapHostMemory();
    }

    void Buffer::Flush(uint64_t size, uint64_t offset) const
    {
        NEPTUNE_PROFILE_ZONE
        
        size = AlignUp(size, static_cast<uint64_t>(4));
        
        CmdList2 cmdList(GetContext());

        cmdList.SetGraphicCmdList();

        cmdList.Begin();

        cmdList.CmdCopyBuffer(m_StagingBuffer->Handle(), 0, m_Buffer.Handle(), offset, size);

        cmdList.End();

        cmdList.SubmitWait();
    }
    
    uint64_t Buffer::GetDeviceAddress() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return 0;
    }
    
    void Buffer::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
        
        DEBUGUTILS_SETOBJECTNAME(m_Buffer, name)
    }
    
}

#endif