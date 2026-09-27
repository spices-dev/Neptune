/**
* @file UniformBufferStandardLayout.cpp.
* @brief The UniformBufferStandardLayout Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "UniformBufferStandardLayout.h"

namespace Neptune::WebGPU::Extension {
    
    UniformBufferStandardLayout::UniformBufferStandardLayout(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_UniformBufferStandardLayout);
    }
}

#endif