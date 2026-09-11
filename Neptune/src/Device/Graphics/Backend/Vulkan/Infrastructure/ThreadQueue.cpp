/**
* @file ThreadQueue.h.
* @brief The ThreadQueue Class Definitions.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ThreadQueue.h"
#include "DebugUtilsObject.h"
#include "Device.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"

namespace Neptune::Vulkan {

    ThreadQueue::ThreadQueue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void ThreadQueue::Create()
    {
        NEPTUNE_PROFILE_ZONE

        uint32_t count = std::min(GetQueueFamilyCount(), NThreadQueue + 1);

        if (count == 1)
        {
            auto queue = CreateSP<Resource::Queue>(GetContext());

            queue->CreateQueue(GetContext().Get<IDevice>()->GetDeviceQueue(GetQueueFamily(), 0));

            m_Queues.Push(queue);

            queue->SetName(ToString());
            
            return;
        }
        
        for (uint32_t i = 1; i < count; ++i)
        {
            auto queue = CreateSP<Resource::Queue>(GetContext());

            queue->CreateQueue(GetContext().Get<IDevice>()->GetDeviceQueue(GetQueueFamily(), i));

            m_Queues.Push(queue);

            queue->SetName(ToString());
        }
    }
    
    uint32_t ThreadQueue::GetQueueFamily() const
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EInfrastructure;
		
        switch (GetEInfrastructure())
        {
            case GraphicThreadQueue:     return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT);
            case ComputeThreadQueue:     return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_COMPUTE_BIT);
            case TransferThreadQueue:    return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_TRANSFER_BIT);
            case VideoEncodeThreadQueue: return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_VIDEO_ENCODE_BIT_KHR);
            case VideoDecodeThreadQueue: return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_VIDEO_DECODE_BIT_KHR);
            case OpticalFlowThreadQueue: return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_OPTICAL_FLOW_BIT_NV);
            default: return 0;
        }
    }
    
    uint32_t ThreadQueue::GetQueueFamilyCount() const
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EInfrastructure;
		
        switch (GetEInfrastructure())
        {
            case GraphicThreadQueue:     return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamilyCount(VK_QUEUE_GRAPHICS_BIT);
            case ComputeThreadQueue:     return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamilyCount(VK_QUEUE_COMPUTE_BIT);
            case TransferThreadQueue:    return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamilyCount(VK_QUEUE_TRANSFER_BIT);
            case VideoEncodeThreadQueue: return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamilyCount(VK_QUEUE_VIDEO_ENCODE_BIT_KHR);
            case VideoDecodeThreadQueue: return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamilyCount(VK_QUEUE_VIDEO_DECODE_BIT_KHR);
            case OpticalFlowThreadQueue: return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamilyCount(VK_QUEUE_OPTICAL_FLOW_BIT_NV);
            default: return 0;
        }
    }
    
}

#endif