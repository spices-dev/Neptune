/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Surface.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Instance.h"

namespace Neptune::Vulkan::Display {

    Surface::Surface(Context& context, EInfrastructure e, WindowImplement implement)
        : Vulkan::Surface(context, e, implement)
    {}

    bool Surface::Create(VkPhysicalDevice physicalDevice)
    {
        NEPTUNE_PROFILE_ZONE
        
        uint32_t displayCount = 0;
        VULKAN_CHECK(vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayCount, nullptr))
        if (!displayCount) return false;
        
        std::vector<VkDisplayPropertiesKHR> displays(displayCount);
        VULKAN_CHECK(vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayCount, displays.data()))
        
        VkDisplayKHR display = displays[0].display;

        uint32_t modeCount = 0;
        VULKAN_CHECK(vkGetDisplayModePropertiesKHR(physicalDevice, display, &modeCount, nullptr))
        if (!modeCount) return false;
        
        std::vector<VkDisplayModePropertiesKHR> modes(modeCount);
        VULKAN_CHECK(vkGetDisplayModePropertiesKHR(physicalDevice, display, &modeCount, modes.data()))
        
        VkDisplayModeKHR mode = modes[0].displayMode;
        VkExtent2D extent     = modes[0].parameters.visibleRegion;
        
        uint32_t planeCount = 0;
        VULKAN_CHECK(vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &planeCount, nullptr))
        if (!planeCount) return false;
        
        std::vector<VkDisplayPlanePropertiesKHR> planes(planeCount);
        VULKAN_CHECK(vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &planeCount, planes.data()))

        uint32_t planeIndex = UINT32_MAX;
        for (uint32_t i = 0; i < planeCount; ++i) 
        {
            if (planes[i].currentDisplay && planes[i].currentDisplay != display) continue;

            uint32_t n = 0;
            VULKAN_CHECK(vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &n, nullptr))
            
            std::vector<VkDisplayKHR> supported(n);
            VULKAN_CHECK(vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &n, supported.data()))
            
            for (uint32_t j = 0; j < n; ++j)
            {
                if (supported[j] == display) { planeIndex = i; break; }
            }
            
            if (planeIndex != UINT32_MAX) break;
        }
        
        if (planeIndex == UINT32_MAX) return false;
        
        VkDisplaySurfaceCreateInfoKHR       info{};
        info.sType                        = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
        info.displayMode                  = mode;
        info.planeIndex                   = planeIndex;
        info.planeStackIndex              = planes[planeIndex].currentStackIndex;
        info.transform                    = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        info.globalAlpha                  = 1.0f;
        info.alphaMode                    = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        info.imageExtent                  = extent;
        
        m_Surface.CreateSurface(GetContext().Get<IInstance>()->Handle(), info);
    }

}

#endif