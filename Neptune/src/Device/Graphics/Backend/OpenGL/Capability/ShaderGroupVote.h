/**
* @file ShaderGroupVote.h.
* @brief The ShaderGroupVote Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IShaderGroupVote = ICapability<class ShaderGroupVote, ECapability::ShaderGroupVote>;
    
    class ShaderGroupVote : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ShaderGroupVote(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderGroupVote() override = default;
    };
}

#endif