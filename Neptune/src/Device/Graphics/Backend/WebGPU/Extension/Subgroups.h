/**
* @file Subgroups.h.
* @brief The Subgroups Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ISubgroups = IExtension<class Subgroups, EExtension::Subgroups>;
    
    class Subgroups : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Subgroups(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Subgroups() override = default;
    };
}

#endif