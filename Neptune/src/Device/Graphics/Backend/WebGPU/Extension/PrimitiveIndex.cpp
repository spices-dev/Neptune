/**
* @file PrimitiveIndex.cpp.
* @brief The PrimitiveIndex Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "PrimitiveIndex.h"

namespace Neptune::WebGPU::Extension {
    
    PrimitiveIndex::PrimitiveIndex(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_PrimitiveIndex);
    }
}

#endif