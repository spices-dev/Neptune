/**
* @file TextureAndSamplerLet.cpp.
* @brief The TextureAndSamplerLet Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureAndSamplerLet.h"

namespace Neptune::WebGPU::Extension {
    
    TextureAndSamplerLet::TextureAndSamplerLet(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_TextureAndSamplerLet);
    }
}

#endif