/**
* @file ShaderSourceSPIRV.cpp.
* @brief The ShaderSourceSPIRV Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "ShaderSourceSPIRV.h"

namespace Neptune::WebGPU::Extension {
    
    ShaderSourceSPIRV::ShaderSourceSPIRV(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddInstanceFeatures(WGPUInstanceFeatureName_ShaderSourceSPIRV);
    }
}

#endif