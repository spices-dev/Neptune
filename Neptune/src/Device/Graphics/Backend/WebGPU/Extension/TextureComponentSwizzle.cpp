/**
* @file TextureComponentSwizzle.cpp.
* @brief The TextureComponentSwizzle Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureComponentSwizzle.h"

namespace Neptune::WebGPU::Extension {
    
    TextureComponentSwizzle::TextureComponentSwizzle(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TextureComponentSwizzle);
    }
}

#endif