/**
* @file Semaphore.h.
* @brief The Semaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using ISemaphore = ICapability<class Semaphore, ECapability::Semaphore>;
    
    class Semaphore : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit Semaphore(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~Semaphore() override = default;
    };
}

#endif