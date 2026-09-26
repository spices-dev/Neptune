/**
* @file Unorm16TextureFormats.cpp.
* @brief The Unorm16TextureFormats Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Unorm16TextureFormats.h"

namespace Neptune::WebGPU::Extension {
    
    Unorm16TextureFormats::Unorm16TextureFormats(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_Unorm16TextureFormats);
    }
}

#endif