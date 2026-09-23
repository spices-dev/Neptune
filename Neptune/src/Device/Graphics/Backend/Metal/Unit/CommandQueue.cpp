/**
* @file CommandQueue.cpp.
* @brief The CommandQueue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "CommandQueue.h"

namespace Neptune::Metal::Unit {

    CommandQueue::~CommandQueue()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
    void CommandQueue::CreateCommandQueue(MTLDevice device)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Handle = device->newCommandQueue4();
    }
}

#endif