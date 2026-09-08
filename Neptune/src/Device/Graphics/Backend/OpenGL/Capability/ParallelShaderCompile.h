/**
* @file ParallelShaderCompile.h.
* @brief The ParallelShaderCompile Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IParallelShaderCompile = ICapability<class ParallelShaderCompile, ECapability::ParallelShaderCompile>;
    
    class ParallelShaderCompile : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ParallelShaderCompile(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ParallelShaderCompile() override = default;
    };
}

#endif