/**
* @file DirectStateAccess.h.
* @brief The DirectStateAccess Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IDirectStateAccess = ICapability<class DirectStateAccess, ECapability::DirectStateAccess>;
    
    class DirectStateAccess : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 45;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit DirectStateAccess(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~DirectStateAccess() override = default;
    };
}

#endif