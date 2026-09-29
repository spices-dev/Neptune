#include "Pchheader.h"
#include "Buffer.h"
#include "Device/Graphics/Frontend/RHI/Buffer.h"

namespace Neptune {

    Buffer::Buffer()
    {
        m_RHIResource = CreateSP<RHI::Buffer>();
    }

    Buffer::Buffer(const BufferCreateInfo& info)
    {
        m_RHIResource = CreateSP<RHI::Buffer>();

        m_RHIResource->CreateBuffer(info);
    }
    
}