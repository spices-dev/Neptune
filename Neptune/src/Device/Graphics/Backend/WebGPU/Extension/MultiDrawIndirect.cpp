/**
* @file MultiDrawIndirect.cpp.
* @brief The MultiDrawIndirect Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "MultiDrawIndirect.h"

namespace Neptune::WebGPU::Extension {
    
    MultiDrawIndirect::MultiDrawIndirect(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_MultiDrawIndirect);
    }
}

#endif