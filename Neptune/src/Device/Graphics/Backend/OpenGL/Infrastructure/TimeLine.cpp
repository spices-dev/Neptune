/**
* @file TimeLine.cpp.
* @brief The TimeLine Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "TimeLine.h"
#include "DebugUtilsObject.h"

namespace Neptune::OpenGL {

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
            auto fence = CreateUP<Unit::Sync>();

            fence->CreateSync();
 
            DEBUGUTILS_SETOBJECTNAME(*fence, ToString())
            
            m_Fences.emplace_back(std::move(fence));
        }
    }

    void TimeLine::Wait(uint32_t frameId) const
    {
        NEPTUNE_PROFILE_ZONE

        m_Fences[frameId % m_Fences.size()]->ClientWait();
    }
    
    void TimeLine::Signal(uint32_t frameId)
    {
        NEPTUNE_PROFILE_ZONE
        
        const auto index = frameId % m_Fences.size();
        
        m_Fences[index] = CreateUP<Unit::Sync>();

        m_Fences[index]->CreateSync();

        DEBUGUTILS_SETOBJECTNAME(*m_Fences[index], ToString())
    }

}

#endif