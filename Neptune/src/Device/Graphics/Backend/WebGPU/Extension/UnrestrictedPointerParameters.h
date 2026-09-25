/**
* @file UnrestrictedPointerParameters.h.
* @brief The UnrestrictedPointerParameters Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IUnrestrictedPointerParameters = IExtension<class UnrestrictedPointerParameters, EExtension::UnrestrictedPointerParameters>;
    
    class UnrestrictedPointerParameters : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit UnrestrictedPointerParameters(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~UnrestrictedPointerParameters() override = default;
    };
}

#endif