/**
* @file BGRA8UnormStorage.cpp.
* @brief The BGRA8UnormStorage Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "BGRA8UnormStorage.h"

namespace Neptune::WebGPU::Extension {
    
    BGRA8UnormStorage::BGRA8UnormStorage(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_BGRA8UnormStorage);
    }
}

#endif