/**
* @file SubgroupId.h.
* @brief The SubgroupId Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ISubgroupId = IExtension<class SubgroupId, EExtension::SubgroupId>;
    
    class SubgroupId : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit SubgroupId(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~SubgroupId() override = default;
    };
}

#endif