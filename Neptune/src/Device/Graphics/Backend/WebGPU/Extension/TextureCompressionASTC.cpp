/**
* @file TextureCompressionASTC.cpp.
* @brief The TextureCompressionASTC Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureCompressionASTC.h"

namespace Neptune::WebGPU::Extension {
    
    TextureCompressionASTC::TextureCompressionASTC(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TextureCompressionASTC);
    }
}

#endif