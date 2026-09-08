/**
* @file IndirectParameters.h.
* @brief The IndirectParameters Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IIndirectParameters = ICapability<class IndirectParameters, ECapability::IndirectParameters>;
    
    class IndirectParameters : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit IndirectParameters(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~IndirectParameters() override = default;
    };
}

#endif