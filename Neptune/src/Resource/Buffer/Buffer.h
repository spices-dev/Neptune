#pragma once
#include "Core/Core.h"
#include "Core/Memory/Enum.h"
#include "Device/Graphics/Frontend/Enum.h"

namespace Neptune {

    namespace RHI {
	
        class Buffer;
    }

    struct BufferCreateInfo
    {
        uint64_t                 size  = 100;
        Graphic::EBufferUsage    usage = Graphic::EBufferUsage::None;
    };
    
    class Buffer
    {
    public:

        Buffer();

        Buffer(const BufferCreateInfo& info);

        virtual ~Buffer() = default;

        SP<RHI::Buffer> GetRHIResource() { return m_RHIResource; }

        void SetName(const std::string& name) { m_Name = name; }

    private:

        std::string           m_Name;
        SP<RHI::Buffer>       m_RHIResource;
    };
}
