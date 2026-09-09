/**
* @file FragmentShaderInterlock.h.
* @brief The FragmentShaderInterlock Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IFragmentShaderInterlock = ICapability<class FragmentShaderInterlock, ECapability::FragmentShaderInterlock>;
    
    class FragmentShaderInterlock : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit FragmentShaderInterlock(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~FragmentShaderInterlock() override = default;
    };
}

#endif