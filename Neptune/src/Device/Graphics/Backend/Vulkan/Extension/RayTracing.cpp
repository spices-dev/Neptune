/**
* @file RayTracing.cpp.
* @brief The RayTracing Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RayTracing.h"

namespace Neptune::Vulkan::Extension {
    
    RayTracing::RayTracing(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_RAY_QUERY_EXTENSION_NAME);
        AddDeviceExtensions(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);
    }
    
}

#endif