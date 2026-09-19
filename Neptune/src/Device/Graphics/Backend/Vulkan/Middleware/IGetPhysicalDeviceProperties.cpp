/**
* @file IGetPhysicalDeviceProperties.cpp.
* @brief The IGetPhysicalDeviceProperties Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IGetPhysicalDeviceProperties.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/GetPhysicalDeviceProperties2.h"

namespace Neptune::Vulkan::Middleware {
	
    UP<IGetPhysicalDeviceProperties> IGetPhysicalDeviceProperties::Create(Context& context)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (context.Get<IExtensions>()->GetContext()->Has<Extension::IGetPhysicalDeviceProperties2>())
        {
            return CreateUP<GetPhysicalDeviceProperties2>();
        }

        return CreateUP<GetPhysicalDeviceProperties>();
    }
    
    void GetPhysicalDeviceProperties::GetProperties(VkPhysicalDevice device, VkPhysicalDeviceProperties2& properties) const
    {
        NEPTUNE_PROFILE_ZONE

        vkGetPhysicalDeviceProperties2(device, &properties);
    }
    
    void GetPhysicalDeviceProperties2::GetProperties(VkPhysicalDevice device, VkPhysicalDeviceProperties2& properties) const
    {
        NEPTUNE_PROFILE_ZONE

        vkGetPhysicalDeviceProperties(device, &properties.properties);
    }
}

#endif