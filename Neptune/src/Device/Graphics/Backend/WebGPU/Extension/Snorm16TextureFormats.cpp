/**
* @file Snorm16TextureFormats.cpp.
* @brief The Snorm16TextureFormats Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Snorm16TextureFormats.h"

namespace Neptune::WebGPU::Extension {
    
    Snorm16TextureFormats::Snorm16TextureFormats(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_Snorm16TextureFormats);
    }
}

#endif