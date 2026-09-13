/**
* @file Semaphore.h.
* @brief The Semaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using ISemaphore = IExtension<class Semaphore, EExtension::Semaphore>;
    
    class Semaphore : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit Semaphore(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~Semaphore() override = default;
    };
}

#endif