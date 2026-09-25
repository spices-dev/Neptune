/**
* @file Packed4x8IntegerDotProduct.cpp.
* @brief The Packed4x8IntegerDotProduct Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Packed4x8IntegerDotProduct.h"

namespace Neptune::WebGPU::Extension {
    
    Packed4x8IntegerDotProduct::Packed4x8IntegerDotProduct(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_Packed4x8IntegerDotProduct);
    }
}

#endif