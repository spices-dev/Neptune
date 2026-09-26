/**
* @file TextureCompressionETC2.cpp.
* @brief The TextureCompressionETC2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureCompressionETC2.h"

namespace Neptune::WebGPU::Extension {
    
    TextureCompressionETC2::TextureCompressionETC2(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TextureCompressionETC2);
    }
}

#endif