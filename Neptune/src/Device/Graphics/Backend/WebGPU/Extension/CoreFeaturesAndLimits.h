/**
* @file CoreFeaturesAndLimits.h.
* @brief The CoreFeaturesAndLimits Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ICoreFeaturesAndLimits = IExtension<class CoreFeaturesAndLimits, EExtension::CoreFeaturesAndLimits>;
    
    class CoreFeaturesAndLimits : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit CoreFeaturesAndLimits(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~CoreFeaturesAndLimits() override = default;
    };
}

#endif