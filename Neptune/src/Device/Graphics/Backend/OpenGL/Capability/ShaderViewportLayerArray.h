/**
* @file ShaderViewportLayerArray.h.
* @brief The ShaderViewportLayerArray Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IShaderViewportLayerArray = ICapability<class ShaderViewportLayerArray, ECapability::ShaderViewportLayerArray>;
    
    class ShaderViewportLayerArray : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ShaderViewportLayerArray(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderViewportLayerArray() override = default;
    };
}

#endif