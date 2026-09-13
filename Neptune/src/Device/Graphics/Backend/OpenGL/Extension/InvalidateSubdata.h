/**
* @file InvalidateSubdata.h.
* @brief The InvalidateSubdata Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IInvalidateSubdata = IExtension<class InvalidateSubdata, EExtension::InvalidateSubdata>;
    
    class InvalidateSubdata : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit InvalidateSubdata(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~InvalidateSubdata() override = default;
    };
}

#endif