/**
* @file IndirectFirstInstance.h.
* @brief The IndirectFirstInstance Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IIndirectFirstInstance = IExtension<class IndirectFirstInstance, EExtension::IndirectFirstInstance>;
    
    class IndirectFirstInstance : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit IndirectFirstInstance(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~IndirectFirstInstance() override = default;
    };
}

#endif