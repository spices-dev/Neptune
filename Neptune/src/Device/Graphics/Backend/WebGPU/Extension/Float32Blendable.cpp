/**
* @file Float32Blendable.cpp.
* @brief The Float32Blendable Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Float32Blendable.h"

namespace Neptune::WebGPU::Extension {
    
    Float32Blendable::Float32Blendable(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_Float32Blendable);
    }
}

#endif