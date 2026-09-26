/**
* @file Float32Blendable.h.
* @brief The Float32Blendable Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IFloat32Blendable = IExtension<class Float32Blendable, EExtension::Float32Blendable>;
    
    class Float32Blendable : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Float32Blendable(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Float32Blendable() override = default;
    };
}

#endif