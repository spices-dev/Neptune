/**
* @file ParallelShaderCompile.h.
* @brief The ParallelShaderCompile Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IParallelShaderCompile = IExtension<class ParallelShaderCompile, EExtension::ParallelShaderCompile>;
    
    class ParallelShaderCompile : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ParallelShaderCompile(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ParallelShaderCompile() override = default;
    };
}

#endif