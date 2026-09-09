/**
* @file BindlessTexture.h.
* @brief The BindlessTexture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IBindlessTexture = ICapability<class BindlessTexture, ECapability::BindlessTexture>;
    
    class BindlessTexture : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit BindlessTexture(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~BindlessTexture() override = default;
    };
}

#endif