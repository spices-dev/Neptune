/**
* @file IGetSurfaceCapabilities.cpp.
* @brief The IGetSurfaceCapabilities Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IGetSurfaceCapabilities.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/GetSurfaceCapabilities2.h"

namespace Neptune::Vulkan::Middleware {
	
    UP<IGetSurfaceCapabilities> IGetSurfaceCapabilities::Create(Context& context)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (context.Get<IExtensions>()->GetContext().Has<Extension::IGetSurfaceCapabilities2>())
        {
            return CreateUP<GetSurfaceCapabilities2>();
        }
        else
        {
            return CreateUP<GetSurfaceCapabilities>();
        }
    }

    void GetSurfaceCapabilities::GetCapabilities(VkPhysicalDevice device, const VkPhysicalDeviceSurfaceInfo2KHR& surfaceInfo, VkSurfaceCapabilities2KHR& surfaceCapabilities) const
    {
        NEPTUNE_PROFILE_ZONE
		
        VULKAN_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surfaceInfo.surface, &surfaceCapabilities.surfaceCapabilities))
    }
    
    void GetSurfaceCapabilities2::GetCapabilities(VkPhysicalDevice device, const VkPhysicalDeviceSurfaceInfo2KHR& surfaceInfo, VkSurfaceCapabilities2KHR& surfaceCapabilities) const
    {
        NEPTUNE_PROFILE_ZONE
		
        VULKAN_CHECK(vkGetPhysicalDeviceSurfaceCapabilities2KHR(device, &surfaceInfo, &surfaceCapabilities))
    }
}

#endif