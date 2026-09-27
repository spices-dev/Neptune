/**
* @file ImmediateAddressSpace.h.
* @brief The ImmediateAddressSpace Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IImmediateAddressSpace = IExtension<class ImmediateAddressSpace, EExtension::ImmediateAddressSpace>;
    
    class ImmediateAddressSpace : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit ImmediateAddressSpace(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~ImmediateAddressSpace() override = default;
    };
}

#endif