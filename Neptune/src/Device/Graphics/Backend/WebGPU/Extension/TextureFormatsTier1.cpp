/**
* @file TextureFormatsTier1.cpp.
* @brief The TextureFormatsTier1 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureFormatsTier1.h"

namespace Neptune::WebGPU::Extension {
    
    TextureFormatsTier1::TextureFormatsTier1(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TextureFormatsTier1);
    }
}

#endif