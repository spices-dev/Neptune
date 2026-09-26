/**
* @file IndirectFirstInstance.cpp.
* @brief The IndirectFirstInstance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "IndirectFirstInstance.h"

namespace Neptune::WebGPU::Extension {
    
    IndirectFirstInstance::IndirectFirstInstance(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_IndirectFirstInstance);
    }
}

#endif