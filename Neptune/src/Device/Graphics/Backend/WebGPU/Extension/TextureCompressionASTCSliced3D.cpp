/**
* @file TextureCompressionASTCSliced3D.cpp.
* @brief The TextureCompressionASTCSliced3D Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureCompressionASTCSliced3D.h"

namespace Neptune::WebGPU::Extension {
    
    TextureCompressionASTCSliced3D::TextureCompressionASTCSliced3D(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TextureCompressionASTCSliced3D);
    }
}

#endif