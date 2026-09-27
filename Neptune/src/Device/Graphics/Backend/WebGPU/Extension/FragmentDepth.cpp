/**
* @file FragmentDepth.cpp.
* @brief The FragmentDepth Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "FragmentDepth.h"

namespace Neptune::WebGPU::Extension {
    
    FragmentDepth::FragmentDepth(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_FragmentDepth);
    }
}

#endif