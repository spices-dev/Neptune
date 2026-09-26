/**
* @file ShaderF16.cpp.
* @brief The ShaderF16 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "ShaderF16.h"

namespace Neptune::WebGPU::Extension {
    
    ShaderF16::ShaderF16(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_ShaderF16);
    }
}

#endif