/**
* @file ClipDistances.h.
* @brief The ClipDistances Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IClipDistances = IExtension<class ClipDistances, EExtension::ClipDistances>;
    
    class ClipDistances : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit ClipDistances(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~ClipDistances() override = default;
    };
}

#endif