/**
* @file UniformBufferStandardLayout.h.
* @brief The UniformBufferStandardLayout Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IUniformBufferStandardLayout = IExtension<class UniformBufferStandardLayout, EExtension::UniformBufferStandardLayout>;
    
    class UniformBufferStandardLayout : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit UniformBufferStandardLayout(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~UniformBufferStandardLayout() override = default;
    };
}

#endif