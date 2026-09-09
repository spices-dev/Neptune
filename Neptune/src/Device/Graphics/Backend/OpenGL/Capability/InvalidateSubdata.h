/**
* @file InvalidateSubdata.h.
* @brief The InvalidateSubdata Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IInvalidateSubdata = ICapability<class InvalidateSubdata, ECapability::InvalidateSubdata>;
    
    class InvalidateSubdata : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit InvalidateSubdata(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~InvalidateSubdata() override = default;
    };
}

#endif