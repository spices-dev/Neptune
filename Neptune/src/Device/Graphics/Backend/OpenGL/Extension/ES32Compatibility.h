/**
* @file ES32Compatibility.h.
* @brief The ES32Compatibility Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IES32Compatibility = IExtension<class ES32Compatibility, EExtension::ES32Compatibility>;
    
    class ES32Compatibility : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ES32Compatibility(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ES32Compatibility() override = default;
    };
}

#endif