/**
* @file Depth32FloatStencil8.h.
* @brief The Depth32FloatStencil8 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IDepth32FloatStencil8 = IExtension<class Depth32FloatStencil8, EExtension::Depth32FloatStencil8>;
    
    class Depth32FloatStencil8 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Depth32FloatStencil8(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Depth32FloatStencil8() override = default;
    };
}

#endif