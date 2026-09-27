/**
* @file SubgroupUniformity.cpp.
* @brief The SubgroupUniformity Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "SubgroupUniformity.h"

namespace Neptune::WebGPU::Extension {
    
    SubgroupUniformity::SubgroupUniformity(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_SubgroupUniformity);
    }
}

#endif