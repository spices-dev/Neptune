/**
* @file CoreFeaturesAndLimits.cpp.
* @brief The CoreFeaturesAndLimits Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "CoreFeaturesAndLimits.h"

namespace Neptune::WebGPU::Extension {
    
    CoreFeaturesAndLimits::CoreFeaturesAndLimits(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_CoreFeaturesAndLimits);
    }
}

#endif