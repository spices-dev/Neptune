/**
* @file LinearIndexing.h.
* @brief The LinearIndexing Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ILinearIndexing = IExtension<class LinearIndexing, EExtension::LinearIndexing>;
    
    class LinearIndexing : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit LinearIndexing(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~LinearIndexing() override = default;
    };
}

#endif