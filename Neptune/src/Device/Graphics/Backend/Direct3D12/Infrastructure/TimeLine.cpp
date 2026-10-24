/**
* @file TimeLine.cpp.
* @brief The TimeLine Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "TimeLine.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Direct3D12 {

    TimeLine::TimeLine(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void TimeLine::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        for (uint32_t i = 0; i < count; ++i)
        {
            auto fence = CreateSP<Unit::Fence>();

            fence->CreateFence(GetContext().Get<IDevice>()->Handle());
 
            m_Fences.emplace_back(fence);

            DEBUGUTILS_SETOBJECTNAME(*fence, ToString())
        }
    }

    void TimeLine::Wait(uint32_t frameId) const
    {
        NEPTUNE_PROFILE_ZONE

        m_Fences[frameId % m_Fences.size()]->Wait();
    }

}

#endif