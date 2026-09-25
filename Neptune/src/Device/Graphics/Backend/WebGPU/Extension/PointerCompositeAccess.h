/**
* @file PointerCompositeAccess.h.
* @brief The PointerCompositeAccess Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IPointerCompositeAccess = IExtension<class PointerCompositeAccess, EExtension::PointerCompositeAccess>;
    
    class PointerCompositeAccess : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit PointerCompositeAccess(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~PointerCompositeAccess() override = default;
    };
}

#endif