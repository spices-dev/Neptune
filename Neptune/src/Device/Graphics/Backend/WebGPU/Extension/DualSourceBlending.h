/**
* @file DualSourceBlending.h.
* @brief The DualSourceBlending Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IDualSourceBlending = IExtension<class DualSourceBlending, EExtension::DualSourceBlending>;
    
    class DualSourceBlending : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit DualSourceBlending(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~DualSourceBlending() override = default;
    };
}

#endif