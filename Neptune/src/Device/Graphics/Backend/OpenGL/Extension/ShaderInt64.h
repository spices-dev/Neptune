/**
* @file ShaderInt64.h.
* @brief The ShaderInt64 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IShaderInt64 = IExtension<class ShaderInt64, EExtension::ShaderInt64>;
    
    class ShaderInt64 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ShaderInt64(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderInt64() override = default;
    };
}

#endif