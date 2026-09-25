/**
* @file TimeLine.cpp.
* @brief The TimeLine Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TimeLine.h"
#include "Instance.h"

namespace Neptune::WebGPU {

    TimeLine::TimeLine(Context& context, EInfrastructure e, uint32_t count)
		: Infrastructure(context, e)
	{
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void TimeLine::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        m_Futures.resize(count);
    }
    
    void TimeLine::SetHandle(uint32_t frameId, WGPUFuture handle)
    {
        NEPTUNE_PROFILE_ZONE
        
        auto p = CreateUP<Unit::Future>();
        
        p->SetHandle(handle);
        
        m_Futures[frameId % m_Futures.size()] = std::move(p);
    }
    
    void TimeLine::Wait(uint32_t frameId) const
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Futures[frameId % m_Futures.size()]->Wait(GetContext().Get<IInstance>()->Handle());
    }

}

#endif