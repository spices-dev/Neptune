/**
* @file TextureCompressionBC.cpp.
* @brief The TextureCompressionBC Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureCompressionBC.h"

namespace Neptune::WebGPU::Extension {
    
    TextureCompressionBC::TextureCompressionBC(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TextureCompressionBC);
    }
}

#endif