/**
* @file ShaderDrawParameters.h.
* @brief The ShaderDrawParameters Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IShaderDrawParameters = ICapability<class ShaderDrawParameters, ECapability::ShaderDrawParameters>;
    
    class ShaderDrawParameters : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ShaderDrawParameters(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderDrawParameters() override = default;
    };
}

#endif