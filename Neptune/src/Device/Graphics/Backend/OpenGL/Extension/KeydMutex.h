/**
* @file KeydMutex.h.
* @brief The KeydMutex Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IKeydMutex = IExtension<class KeydMutex, EExtension::KeydMutex>;
    
    class KeydMutex : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit KeydMutex(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~KeydMutex() override = default;
    };
}

#endif