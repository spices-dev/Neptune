/**
* @file Robustness.h.
* @brief The Robustness Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IRobustness = ICapability<class Robustness, ECapability::Robustness>;
    
    class Robustness : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 45;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit Robustness(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~Robustness() override = default;
    };
}

#endif