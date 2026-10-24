/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Buffer.h"
#include "Core/Math/Math.h"
#include "CmdList2.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Direct3D12 {
    
    void Buffer::CreateBuffer(const BufferCreateInfo& info)
    {
        NEPTUNE_PROFILE_ZONE
        
        auto size = AlignUp(info.size, static_cast<uint64_t>(256));
        
        D3D12_RESOURCE_DESC                   desc{};
        desc.Dimension                      = D3D12_RESOURCE_DIMENSION_BUFFER;
        desc.Width                          = size;
        desc.Height                         = 1;
        desc.DepthOrArraySize               = 1;
        desc.MipLevels                      = 1;
        desc.Format                         = DXGI_FORMAT_UNKNOWN;
        desc.Layout                         = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        
        m_Buffer.CreateBuffer(desc, D3D12_RESOURCE_STATE_COMMON, D3D12_HEAP_TYPE_DEFAULT);
    }

    void Buffer::WriteToBuffer(const void* data, uint64_t size)
    {
        NEPTUNE_PROFILE_ZONE
        
        size = AlignUp(size, static_cast<uint64_t>(256));
        
        m_StagingBuffer = CreateUP<Resource::Buffer>(GetContext());
        
        D3D12_RESOURCE_DESC                   desc{};
        desc.Dimension                      = D3D12_RESOURCE_DIMENSION_BUFFER;
        desc.Width                          = size;
        desc.Height                         = 1;
        desc.DepthOrArraySize               = 1;
        desc.MipLevels                      = 1;
        desc.Format                         = DXGI_FORMAT_UNKNOWN;
        desc.Layout                         = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

        m_StagingBuffer->CreateBuffer(desc, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_HEAP_TYPE_UPLOAD);

        m_StagingBuffer->WriteToBuffer(data);
    
        m_StagingBuffer->UnapHostMemory();
    }

    void Buffer::Flush(uint64_t size, uint64_t offset) const
    {
        NEPTUNE_PROFILE_ZONE
        
        size = AlignUp(size, static_cast<uint64_t>(256));
        
        CmdList2 cmdList(GetContext());

        cmdList.SetGraphicCmdList();

        cmdList.Begin();

        {
            auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
                m_Buffer.Handle(),
                D3D12_RESOURCE_STATE_COMMON,
                D3D12_RESOURCE_STATE_COPY_DEST
            );
        
            //cmdList.CmdInsertBarrier(barrier);
        }
        
        //cmdList.CmdCopyBuffer(m_StagingBuffer->Handle(), 0, m_Buffer.Handle(), offset, size);

        {
            auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
                m_Buffer.Handle(),
                D3D12_RESOURCE_STATE_COPY_DEST,
                D3D12_RESOURCE_STATE_COMMON
            );
        
            //cmdList.CmdInsertBarrier(barrier);
        }
        
        cmdList.End();

        cmdList.SubmitWait();
    }
    
    uint64_t Buffer::GetDeviceAddress() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return m_Buffer.GetDeviceAddress();
    }
    
    void Buffer::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
        
        DEBUGUTILS_SETOBJECTNAME(m_Buffer.IHandle(), name)
    }
    
}

#endif