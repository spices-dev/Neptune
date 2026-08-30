/**
* @file ShaderDebugger.h.
* @brief The ShaderDebugger Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using IShaderDebugger = ILayer<class ShaderDebugger, ELayer::ShaderDebugger>;

    class ShaderDebugger : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit ShaderDebugger(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~ShaderDebugger() override = default;
    };
}

#endif