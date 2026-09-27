/**
* @file ChromiumExperimentalSubgroupMatrix.cpp.
* @brief The ChromiumExperimentalSubgroupMatrix Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "ChromiumExperimentalSubgroupMatrix.h"

namespace Neptune::WebGPU::Extension {
    
    ChromiumExperimentalSubgroupMatrix::ChromiumExperimentalSubgroupMatrix(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_ChromiumExperimentalSubgroupMatrix);
    }
}

#endif