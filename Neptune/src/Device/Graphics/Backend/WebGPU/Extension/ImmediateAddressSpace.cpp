/**
* @file ImmediateAddressSpace.cpp.
* @brief The ImmediateAddressSpace Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "ImmediateAddressSpace.h"

namespace Neptune::WebGPU::Extension {
    
    ImmediateAddressSpace::ImmediateAddressSpace(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_ImmediateAddressSpace);
    }
}

#endif