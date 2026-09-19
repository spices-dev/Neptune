/**
* @file TimeLine.cpp.
* @brief The TimeLine Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "TimeLine.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

    TimeLine::TimeLine(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
        , m_TimeLine(Middleware::ITimeLine::Create(context, count))
    {
        NEPTUNE_PROFILE_ZONE
        
        SetName();
    }
    
    void TimeLine::Wait(uint64_t value) const
    {
        NEPTUNE_PROFILE_ZONE
        
        m_TimeLine->Wait(value);
    }
    
    VkSemaphore TimeLine::Semaphore(uint64_t frameId) const
    {
        NEPTUNE_PROFILE_ZONE
        
        return m_TimeLine->Semaphore(frameId);
    }
    
    VkFence TimeLine::Fence(uint64_t frameId) const
    {
        NEPTUNE_PROFILE_ZONE
        
        return m_TimeLine->Fence(frameId);
    }

    void TimeLine::SetName() const
    {
        NEPTUNE_PROFILE_ZONE

        using enum EInfrastructure;
        
        switch (GetEInfrastructure())
        {
            case GraphicTimeLine:
            {
                m_TimeLine->SetName("Graphic");
                break;
            }
            case ComputeTimeLine:
            {
                m_TimeLine->SetName("Compute");
                break;
            }
            default: break;
        }
    }
}

#endif