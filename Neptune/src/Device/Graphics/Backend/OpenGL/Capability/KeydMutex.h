/**
* @file KeydMutex.h.
* @brief The KeydMutex Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IKeydMutex = ICapability<class KeydMutex, ECapability::KeydMutex>;
    
    class KeydMutex : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit KeydMutex(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~KeydMutex() override = default;
    };
}

#endif