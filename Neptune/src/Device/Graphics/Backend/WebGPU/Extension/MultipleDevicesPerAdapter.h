/**
* @file MultipleDevicesPerAdapter.h.
* @brief The MultipleDevicesPerAdapter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IMultipleDevicesPerAdapter = IExtension<class MultipleDevicesPerAdapter, EExtension::MultipleDevicesPerAdapter>;
    
    class MultipleDevicesPerAdapter : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit MultipleDevicesPerAdapter(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~MultipleDevicesPerAdapter() override = default;
    };
}

#endif