/**
* @file VideoEncode.cpp.
* @brief The VideoEncode Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "VideoEncode.h"

namespace Neptune::Vulkan::Extension {
    
    VideoEncode::VideoEncode(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_VIDEO_QUEUE_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME);
    }
    
    void VideoEncode::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_VideoMaintenance1Features);
    }
    
    bool VideoEncode::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "VideoMaintenance1 [ videoMaintenance1 ] : " << m_VideoMaintenance1Features.videoMaintenance1;
        
        if (!m_VideoMaintenance1Features.videoMaintenance1)
        {
            return false;
        }

        return true;
    }
}

#endif