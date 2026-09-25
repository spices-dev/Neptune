/**
* @file PointerCompositeAccess.cpp.
* @brief The PointerCompositeAccess Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "PointerCompositeAccess.h"

namespace Neptune::WebGPU::Extension {
    
    PointerCompositeAccess::PointerCompositeAccess(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_PointerCompositeAccess);
    }
}

#endif