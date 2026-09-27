/**
* @file SubgroupSizeControl.h.
* @brief The SubgroupSizeControl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ISubgroupSizeControl = IExtension<class SubgroupSizeControl, EExtension::SubgroupSizeControl>;
    
    class SubgroupSizeControl : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit SubgroupSizeControl(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~SubgroupSizeControl() override = default;
    };
}

#endif