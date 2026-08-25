/**
* @file RayTracing.cpp.
* @brief The RayTracing Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RayTracing.h"

namespace Neptune::Vulkan::Extension {
    
    RayTracing::RayTracing()
    {
        NEPTUNE_PROFILE_ZONE
        
        AddDeviceExtensions(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_RAY_QUERY_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);
    }
    
}

#endif