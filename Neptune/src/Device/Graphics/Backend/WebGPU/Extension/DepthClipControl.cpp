/**
* @file DepthClipControl.cpp.
* @brief The DepthClipControl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "DepthClipControl.h"

namespace Neptune::WebGPU::Extension {
    
    DepthClipControl::DepthClipControl(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_DepthClipControl);
    }
}

#endif