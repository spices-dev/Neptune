/**
* @file DispatchSemaphore.cpp.
* @brief The DispatchSemaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "DispatchSemaphore.h"

namespace Neptune::Metal {
	
    DispatchSemaphore::DispatchSemaphore(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE
        
        Create(count);
    }
    
    void DispatchSemaphore::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_DispatchSemaphore.CreateDispatchSemaphore(count);
    }
    
    void DispatchSemaphore::Wait()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_DispatchSemaphore.Wait();
    }
    
    void DispatchSemaphore::Signal()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_DispatchSemaphore.Signal();
    }
}

#endif