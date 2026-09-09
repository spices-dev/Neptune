/**
* @file Debug.h.
* @brief The Debug Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IDebug = ICapability<class Debug, ECapability::Debug>;
    
    class Debug : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit Debug(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~Debug() override = default;
        
    private:
        
        GLint m_MaxMessageLength;
        GLint m_MaxLoggedMessages;
        GLint m_MaxGroupStackDepth;
    };
}

#endif