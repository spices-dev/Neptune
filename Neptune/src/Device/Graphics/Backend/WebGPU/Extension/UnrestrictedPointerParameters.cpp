/**
* @file UnrestrictedPointerParameters.cpp.
* @brief The UnrestrictedPointerParameters Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "UnrestrictedPointerParameters.h"

namespace Neptune::WebGPU::Extension {
    
    UnrestrictedPointerParameters::UnrestrictedPointerParameters(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_UnrestrictedPointerParameters);
    }
}

#endif