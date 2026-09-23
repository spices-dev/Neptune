/**
* @file DispatchSemaphore.cpp.
* @brief The DispatchSemaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "DispatchSemaphore.h"

namespace Neptune::Metal::Unit {

    DispatchSemaphore::~DispatchSemaphore()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        dispatch_release(m_Handle);
    }
    
    void DispatchSemaphore::CreateDispatchSemaphore(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Handle = dispatch_semaphore_create(count);
    }
    
    void DispatchSemaphore::Wait()
    {
        NEPTUNE_PROFILE_ZONE
        
        dispatch_semaphore_wait(m_Handle);
    }
    
    void DispatchSemaphore::Signal()
    {
        NEPTUNE_PROFILE_ZONE
        
        dispatch_semaphore_signal(m_Handle);
    }
}

#endif