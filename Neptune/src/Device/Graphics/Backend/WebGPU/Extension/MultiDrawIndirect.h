/**
* @file MultiDrawIndirect.h.
* @brief The MultiDrawIndirect Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IMultiDrawIndirect = IExtension<class MultiDrawIndirect, EExtension::MultiDrawIndirect>;
    
    class MultiDrawIndirect : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit MultiDrawIndirect(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~MultiDrawIndirect() override = default;
    };
}

#endif