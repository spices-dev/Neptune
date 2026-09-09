/**
* @file TimelineSemaphore.h.
* @brief The TimelineSemaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using ITimelineSemaphore = ICapability<class TimelineSemaphore, ECapability::TimelineSemaphore>;
    
    class TimelineSemaphore : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit TimelineSemaphore(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TimelineSemaphore() override = default;
    };
}

#endif