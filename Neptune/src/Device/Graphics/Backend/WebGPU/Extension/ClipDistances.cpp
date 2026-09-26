/**
* @file ClipDistances.cpp.
* @brief The ClipDistances Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "ClipDistances.h"

namespace Neptune::WebGPU::Extension {
    
    ClipDistances::ClipDistances(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_ClipDistances);
    }
}

#endif