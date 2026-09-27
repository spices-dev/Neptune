/**
* @file SubgroupSizeControl.cpp.
* @brief The SubgroupSizeControl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "SubgroupSizeControl.h"

namespace Neptune::WebGPU::Extension {
    
    SubgroupSizeControl::SubgroupSizeControl(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_SubgroupSizeControl);
    }
}

#endif