/**
* @file ChromiumExperimentalSubgroupMatrix.h.
* @brief The ChromiumExperimentalSubgroupMatrix Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IChromiumExperimentalSubgroupMatrix = IExtension<class ChromiumExperimentalSubgroupMatrix, EExtension::ChromiumExperimentalSubgroupMatrix>;
    
    class ChromiumExperimentalSubgroupMatrix : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit ChromiumExperimentalSubgroupMatrix(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~ChromiumExperimentalSubgroupMatrix() override = default;
    };
}

#endif