/**
* @file TimerQuery.h.
* @brief The TimerQuery Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using ITimerQuery = IExtension<class TimerQuery, EExtension::TimerQuery>;
    
    class TimerQuery : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 33;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit TimerQuery(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TimerQuery() override = default;
        
    private:
        
        GLint m_TimestampBits;
        GLint m_TimeElapsedBits;
    };
}

#endif