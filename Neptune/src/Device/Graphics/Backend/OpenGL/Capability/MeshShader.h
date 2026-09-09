/**
* @file MeshShader.h.
* @brief The MeshShader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IMeshShader = ICapability<class MeshShader, ECapability::MeshShader>;
    
    class MeshShader : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit MeshShader(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~MeshShader() override = default;
    };
}

#endif