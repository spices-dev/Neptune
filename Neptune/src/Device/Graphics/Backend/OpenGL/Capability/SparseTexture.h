/**
* @file SparseTexture.h.
* @brief The SparseTexture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using ISparseTexture = ICapability<class SparseTexture, ECapability::SparseTexture>;
    
    class SparseTexture : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit SparseTexture(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~SparseTexture() override = default;
    };
}

#endif