/**
* @file CommandBuffer.cpp.
* @brief The CommandBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "CommandBuffer.h"

namespace Neptune::Metal::Unit {

    CommandBuffer::~CommandBuffer()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
    void CommandBuffer::CreateCommandBuffer(MTLCommandQueue commandQueue)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Handle = commandQueue->newCommandBuffer();
    }
}

#endif