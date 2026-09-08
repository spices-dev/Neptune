/**
* @file ClipControl.h.
* @brief The ClipControl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IClipControl = ICapability<class ClipControl, ECapability::ClipControl>;
    
    class ClipControl : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 45;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ClipControl(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ClipControl() override = default;
    };
}

#endif