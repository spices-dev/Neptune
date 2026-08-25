/**
* @file VideoDecode.cpp.
* @brief The VideoDecode Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "VideoDecode.h"

namespace Neptune::Vulkan::Extension {
    
    VideoDecode::VideoDecode()
    {
        NEPTUNE_PROFILE_ZONE
        
        AddDeviceExtensions(VK_KHR_VIDEO_QUEUE_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME);
    }
    
}

#endif