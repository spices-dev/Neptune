/**
* @file TimedWaitAny.cpp.
* @brief The TimedWaitAny Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TimedWaitAny.h"

namespace Neptune::WebGPU::Extension {
    
    TimedWaitAny::TimedWaitAny(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddInstanceFeatures(WGPUInstanceFeatureName_TimedWaitAny);
    }
    
    bool TimedWaitAny::IsInstanceLimitsSatisfied(WGPUInstanceLimits limits) const
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "TimedWaitAny [ timedWaitAnyMaxCount ] : " << limits.timedWaitAnyMaxCount;
        
        if (limits.timedWaitAnyMaxCount < WaitTimeoutNS)
        {
            return false;
        }
        
        return true;
    }
}

#endif