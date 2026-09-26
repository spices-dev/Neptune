/**
* @file DepthClipControl.h.
* @brief The DepthClipControl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IDepthClipControl = IExtension<class DepthClipControl, EExtension::DepthClipControl>;
    
    class DepthClipControl : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit DepthClipControl(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~DepthClipControl() override = default;
    };
}

#endif