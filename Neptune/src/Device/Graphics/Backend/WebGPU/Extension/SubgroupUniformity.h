/**
* @file SubgroupUniformity.h.
* @brief The SubgroupUniformity Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ISubgroupUniformity = IExtension<class SubgroupUniformity, EExtension::SubgroupUniformity>;
    
    class SubgroupUniformity : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit SubgroupUniformity(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~SubgroupUniformity() override = default;
    };
}

#endif