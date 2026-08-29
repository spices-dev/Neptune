/**
* @file ShaderObject.h.
* @brief The ShaderObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IShaderObject = ILayer<class ShaderObject, ELayer::ShaderObject>;

    class ShaderObject : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit ShaderObject(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~ShaderObject() override = default;
    };
}

#endif