/**
* @file SubgroupId.cpp.
* @brief The SubgroupId Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "SubgroupId.h"

namespace Neptune::WebGPU::Extension {
    
    SubgroupId::SubgroupId(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_SubgroupId);
    }
}

#endif