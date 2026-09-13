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
        
    private:
        
        GLint m_MaxValueDifference;
    };
}

#endif