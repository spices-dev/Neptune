/**
* @file PrimitiveIndex.h.
* @brief The PrimitiveIndex Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IPrimitiveIndex = IExtension<class PrimitiveIndex, EExtension::PrimitiveIndex>;
    
    class PrimitiveIndex : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit PrimitiveIndex(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~PrimitiveIndex() override = default;
    };
}

#endif