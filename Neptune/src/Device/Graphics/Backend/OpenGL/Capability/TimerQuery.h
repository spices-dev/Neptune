/**
* @file TimerQuery.h.
* @brief The TimerQuery Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using ITimerQuery = ICapability<class TimerQuery, ECapability::TimerQuery>;
    
    class TimerQuery : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 33;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit TimerQuery(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TimerQuery() override = default;
    };
}

#endif