/**
* @file Float32Filterable.cpp.
* @brief The Float32Filterable Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Float32Filterable.h"

namespace Neptune::WebGPU::Extension {
    
    Float32Filterable::Float32Filterable(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_Float32Filterable);
    }
}

#endif