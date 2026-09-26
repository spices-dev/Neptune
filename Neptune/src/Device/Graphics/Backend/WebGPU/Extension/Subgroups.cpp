/**
* @file Subgroups.cpp.
* @brief The Subgroups Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Subgroups.h"

namespace Neptune::WebGPU::Extension {
    
    Subgroups::Subgroups(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_Subgroups);
    }
}

#endif