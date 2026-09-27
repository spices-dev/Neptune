/**
* @file SwizzleAssignment.h.
* @brief The SwizzleAssignment Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ISwizzleAssignment = IExtension<class SwizzleAssignment, EExtension::SwizzleAssignment>;
    
    class SwizzleAssignment : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit SwizzleAssignment(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~SwizzleAssignment() override = default;
    };
}

#endif