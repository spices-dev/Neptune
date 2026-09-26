/**
* @file ShaderF16.h.
* @brief The ShaderF16 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IShaderF16 = IExtension<class ShaderF16, EExtension::ShaderF16>;
    
    class ShaderF16 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit ShaderF16(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~ShaderF16() override = default;
    };
}

#endif