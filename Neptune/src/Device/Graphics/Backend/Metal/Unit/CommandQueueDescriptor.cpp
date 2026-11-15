/**
* @file CommandQueueDescriptor.cpp.
* @brief The CommandQueueDescriptor Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "CommandQueueDescriptor.h"

namespace Neptune::Metal::Unit {

    CommandQueueDescriptor::~CommandQueueDescriptor()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
    void CommandQueueDescriptor::CreateCommandQueueDescriptor()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Handle = MTL4::CommandQueueDescriptor::alloc()->init();
    }
}

#endif
