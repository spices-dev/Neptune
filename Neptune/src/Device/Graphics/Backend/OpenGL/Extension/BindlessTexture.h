/**
* @file BindlessTexture.h.
* @brief The BindlessTexture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IBindlessTexture = IExtension<class BindlessTexture, EExtension::BindlessTexture>;
    
    class BindlessTexture : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit BindlessTexture(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~BindlessTexture() override = default;
    };
}

#endif