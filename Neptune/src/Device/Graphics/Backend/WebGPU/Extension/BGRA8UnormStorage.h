/**
* @file BGRA8UnormStorage.h.
* @brief The BGRA8UnormStorage Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IBGRA8UnormStorage = IExtension<class BGRA8UnormStorage, EExtension::BGRA8UnormStorage>;
    
    class BGRA8UnormStorage : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit BGRA8UnormStorage(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~BGRA8UnormStorage() override = default;
    };
}

#endif