/**
* @file LinearIndexing.cpp.
* @brief The LinearIndexing Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "LinearIndexing.h"

namespace Neptune::WebGPU::Extension {
    
    LinearIndexing::LinearIndexing(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_LinearIndexing);
    }
}

#endif