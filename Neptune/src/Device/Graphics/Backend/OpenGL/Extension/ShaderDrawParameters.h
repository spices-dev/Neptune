/**
* @file ShaderDrawParameters.h.
* @brief The ShaderDrawParameters Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IShaderDrawParameters = IExtension<class ShaderDrawParameters, EExtension::ShaderDrawParameters>;
    
    class ShaderDrawParameters : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ShaderDrawParameters(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderDrawParameters() override = default;
    };
}

#endif