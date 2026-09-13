/**
* @file ShaderGroupVote.h.
* @brief The ShaderGroupVote Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IShaderGroupVote = IExtension<class ShaderGroupVote, EExtension::ShaderGroupVote>;
    
    class ShaderGroupVote : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ShaderGroupVote(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderGroupVote() override = default;
    };
}

#endif