/**
* @file TimedWaitAny.h.
* @brief The TimedWaitAny Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITimedWaitAny = IExtension<class TimedWaitAny, EExtension::TimedWaitAny>;
    
    class TimedWaitAny : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TimedWaitAny(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TimedWaitAny() override = default;
        
        /**
        * @brief Is Instance Limits satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsInstanceLimitsSatisfied(WGPUInstanceLimits limits) const override;
    };
}

#endif