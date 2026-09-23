/**
* @file AutoreleasePool.cpp.
* @brief The AutoreleasePool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "AutoreleasePool.h"

namespace Neptune::Metal {
	
    AutoreleasePool::AutoreleasePool(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

    void AutoreleasePool::Init()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_AutoreleasePool = CreateUP<Unit::AutoreleasePool>();
        
        m_AutoreleasePool->CreateAutoreleasePool();
    }
    
    void AutoreleasePool::Release()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_AutoreleasePool.reset();
    }
    
}

#endif