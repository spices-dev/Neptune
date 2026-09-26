/**
* @file TimestampQuery.cpp.
* @brief The TimestampQuery Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TimestampQuery.h"

namespace Neptune::WebGPU::Extension {
    
    TimestampQuery::TimestampQuery(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddAdapterFeatures(WGPUFeatureName_TimestampQuery);
    }
}

#endif