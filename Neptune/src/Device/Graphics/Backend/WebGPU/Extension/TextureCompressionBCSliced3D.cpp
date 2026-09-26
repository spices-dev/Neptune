/**
* @file TextureCompressionBCSliced3D.cpp.
* @brief The TextureCompressionBCSliced3D Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureCompressionBCSliced3D.h"

namespace Neptune::WebGPU::Extension {
    
    TextureCompressionBCSliced3D::TextureCompressionBCSliced3D(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TextureCompressionBCSliced3D);
    }
}

#endif