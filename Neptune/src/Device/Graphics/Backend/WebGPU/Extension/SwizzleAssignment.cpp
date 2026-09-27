/**
* @file SwizzleAssignment.cpp.
* @brief The SwizzleAssignment Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "SwizzleAssignment.h"

namespace Neptune::WebGPU::Extension {
    
    SwizzleAssignment::SwizzleAssignment(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_SwizzleAssignment);
    }
}

#endif