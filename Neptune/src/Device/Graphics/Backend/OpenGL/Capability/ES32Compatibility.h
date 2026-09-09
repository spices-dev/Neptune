/**
* @file ES32Compatibility.h.
* @brief The ES32Compatibility Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IES32Compatibility = ICapability<class ES32Compatibility, ECapability::ES32Compatibility>;
    
    class ES32Compatibility : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ES32Compatibility(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ES32Compatibility() override = default;
    };
}

#endif