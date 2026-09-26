/**
* @file Depth32FloatStencil8.cpp.
* @brief The Depth32FloatStencil8 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Depth32FloatStencil8.h"

namespace Neptune::WebGPU::Extension {
    
    Depth32FloatStencil8::Depth32FloatStencil8(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_Depth32FloatStencil8);
    }
}

#endif