/**
* @file DualSourceBlending.cpp.
* @brief The DualSourceBlending Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "DualSourceBlending.h"

namespace Neptune::WebGPU::Extension {
    
    DualSourceBlending::DualSourceBlending(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_DualSourceBlending);
    }
}

#endif