/**
* @file TextureCompressionUnaligned.cpp.
* @brief The TextureCompressionUnaligned Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureCompressionUnaligned.h"

namespace Neptune::WebGPU::Extension {
    
    TextureCompressionUnaligned::TextureCompressionUnaligned(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TextureCompressionUnaligned);
    }
}

#endif