/**
* @file ReadonlyAndReadwriteStorageTextures.cpp.
* @brief The ReadonlyAndReadwriteStorageTextures Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "ReadonlyAndReadwriteStorageTextures.h"

namespace Neptune::WebGPU::Extension {
    
    ReadonlyAndReadwriteStorageTextures::ReadonlyAndReadwriteStorageTextures(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures);
    }
}

#endif