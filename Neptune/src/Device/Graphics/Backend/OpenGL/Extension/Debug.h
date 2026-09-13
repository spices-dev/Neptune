/**
* @file Debug.h.
* @brief The Debug Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IDebug = IExtension<class Debug, EExtension::Debug>;
    
    class Debug : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit Debug(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~Debug() override = default;
        
        /**
        * @brief Query Extension Properties.
        */
        void QueryProperties() override;
        
        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsPropertiesSatisfied() override;
        
    private:
        
        GLint m_MaxMessageLength;
        GLint m_MaxLoggedMessages;
        GLint m_MaxGroupStackDepth;
    };
}

#endif