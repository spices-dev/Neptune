/**
* @file TextureFormatsTier2.cpp.
* @brief The TextureFormatsTier2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureFormatsTier2.h"

namespace Neptune::WebGPU::Extension {
    
    TextureFormatsTier2::TextureFormatsTier2(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TextureFormatsTier2);
    }
}

#endif