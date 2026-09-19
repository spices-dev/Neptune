/**
* @file Queue.cpp.
* @brief The Queue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Queue.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"
#include "DebugUtilsObject.h"
#include "Device.h"
#include "Extensions.h"

namespace Neptune::Vulkan {

    Queue::Queue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
        , m_QueueSubmit(Middleware::IQueueSubmit::Create(context))
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Queue::Create()
    {
        NEPTUNE_PROFILE_ZONE

        m_Queue.SetHandle(GetContext().Get<IDevice>()->GetDeviceQueue(GetQueueFamily(), 0));
        
        DEBUGUTILS_SETOBJECTNAME(m_Queue, ToString())
    }

    void Queue::Submit(const VkSubmitInfo2& info, VkFence fence) const
    {
        NEPTUNE_PROFILE_ZONE

        m_QueueSubmit->Submit(&m_Queue, info, fence);
    }
    
    void Queue::Wait() const
    {
        NEPTUNE_PROFILE_ZONE

        m_Queue.Wait();
    }
    
    uint32_t Queue::GetQueueFamily() const
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EInfrastructure;
		
        switch (GetEInfrastructure())
        {
            case GraphicQueue: return GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT);
            case PresentQueue: return GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->GetPresentQueueFamily();
            case ComputeQueue: return GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_COMPUTE_BIT);
            default: return 0;
        }
    }
}

#endif