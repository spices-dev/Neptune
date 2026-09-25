/**
* @file ShaderSourceSPIRV.h.
* @brief The ShaderSourceSPIRV Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IShaderSourceSPIRV = IExtension<class ShaderSourceSPIRV, EExtension::ShaderSourceSPIRV>;
    
    class ShaderSourceSPIRV : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit ShaderSourceSPIRV(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~ShaderSourceSPIRV() override = default;
    };
}

#endif