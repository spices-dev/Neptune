/**
* @file Float32Filterable.h.
* @brief The Float32Filterable Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IFloat32Filterable = IExtension<class Float32Filterable, EExtension::Float32Filterable>;
    
    class Float32Filterable : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Float32Filterable(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Float32Filterable() override = default;
    };
}

#endif