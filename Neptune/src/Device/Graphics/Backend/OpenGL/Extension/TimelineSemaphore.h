/**
* @file TimelineSemaphore.h.
* @brief The TimelineSemaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using ITimelineSemaphore = IExtension<class TimelineSemaphore, EExtension::TimelineSemaphore>;
    
    class TimelineSemaphore : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit TimelineSemaphore(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TimelineSemaphore() override = default;
        
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
        
        GLint m_MaxValueDifference;
    };
}

#endif