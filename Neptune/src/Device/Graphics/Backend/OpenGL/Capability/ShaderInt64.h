/**
* @file ShaderInt64.h.
* @brief The ShaderInt64 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IShaderInt64 = ICapability<class ShaderInt64, ECapability::ShaderInt64>;
    
    class ShaderInt64 : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ShaderInt64(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderInt64() override = default;
    };
}

#endif