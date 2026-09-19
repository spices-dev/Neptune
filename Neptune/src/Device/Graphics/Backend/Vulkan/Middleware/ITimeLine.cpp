/**
* @file ITimeLine.cpp.
* @brief The ITimeLine Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ITimeLine.h"
#include "TimeLine.h"
#include "TimeLine2.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/TimelineSemaphore.h"

namespace Neptune::Vulkan::Middleware {
	
    UP<ITimeLine> ITimeLine::Create(Context& context, uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE
		
        if (context.Get<IExtensions>()->GetContext()->Has<Extension::ITimelineSemaphore>())
        {
            return CreateUP<TimeLine2>(context);
        }
		
        return CreateUP<TimeLine>(context, count);
    }
}

#endif