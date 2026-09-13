/**
* @file ShaderViewportLayerArray.h.
* @brief The ShaderViewportLayerArray Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IShaderViewportLayerArray = IExtension<class ShaderViewportLayerArray, EExtension::ShaderViewportLayerArray>;
    
    class ShaderViewportLayerArray : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ShaderViewportLayerArray(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderViewportLayerArray() override = default;
    };
}

#endif