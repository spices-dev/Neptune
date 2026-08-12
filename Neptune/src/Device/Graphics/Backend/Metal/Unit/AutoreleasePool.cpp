/**
* @file AutoreleasePool.cpp.
* @brief The AutoreleasePool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "AutoreleasePool.h"

namespace Neptune::Metal::Unit {

    AutoreleasePool::~AutoreleasePool()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
    void AutoreleasePool::CreateAutoreleasePool()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Handle = NS::AutoreleasePool::alloc()->init();
    }
    
}

#endif