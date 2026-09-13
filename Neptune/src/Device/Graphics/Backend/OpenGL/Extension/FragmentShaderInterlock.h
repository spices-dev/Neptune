/**
* @file FragmentShaderInterlock.h.
* @brief The FragmentShaderInterlock Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IFragmentShaderInterlock = IExtension<class FragmentShaderInterlock, EExtension::FragmentShaderInterlock>;
    
    class FragmentShaderInterlock : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit FragmentShaderInterlock(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~FragmentShaderInterlock() override = default;
    };
}

#endif