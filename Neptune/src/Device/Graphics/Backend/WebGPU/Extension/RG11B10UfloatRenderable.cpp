/**
* @file RG11B10UfloatRenderable.cpp.
* @brief The RG11B10UfloatRenderable Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "RG11B10UfloatRenderable.h"

namespace Neptune::WebGPU::Extension {
    
    RG11B10UfloatRenderable::RG11B10UfloatRenderable(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_RG11B10UfloatRenderable);
    }
}

#endif