/**
* @file DirectStateAccess.h.
* @brief The DirectStateAccess Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IDirectStateAccess = IExtension<class DirectStateAccess, EExtension::DirectStateAccess>;
    
    class DirectStateAccess : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 45;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit DirectStateAccess(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~DirectStateAccess() override = default;
    };
}

#endif