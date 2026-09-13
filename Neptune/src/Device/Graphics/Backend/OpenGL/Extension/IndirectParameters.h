/**
* @file IndirectParameters.h.
* @brief The IndirectParameters Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IIndirectParameters = IExtension<class IndirectParameters, EExtension::IndirectParameters>;
    
    class IndirectParameters : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit IndirectParameters(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~IndirectParameters() override = default;
    };
}

#endif