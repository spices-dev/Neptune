/**
* @file Display.cpp.
* @brief The Display Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Display.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Instance.h"

namespace Neptune::Vulkan::Resource {

    void Display::CreateDisplay()
    {
        NEPTUNE_PROFILE_ZONE
        
        auto physicalDevice = GetContext().Get<IPhysicalDevice>()->Handle();
        
        uint32_t displayCount = 0;
        VULKAN_CHECK(vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayCount, nullptr))
        
        std::vector<VkDisplayPropertiesKHR> displays(displayCount);
        VULKAN_CHECK(vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayCount, displays.data()))
        
        VkDisplayKHR display = displays[0].display;

        uint32_t modeCount = 0;
        VULKAN_CHECK(vkGetDisplayModePropertiesKHR(physicalDevice, display, &modeCount, nullptr))
        
        std::vector<VkDisplayModePropertiesKHR> modes(modeCount);
        VULKAN_CHECK(vkGetDisplayModePropertiesKHR(physicalDevice, display, &modeCount, modes.data()))
        
        VkDisplayModeKHR mode = modes[0].displayMode;
        VkExtent2D extent     = modes[0].parameters.visibleRegion;
        
        uint32_t planeCount = 0;
        VULKAN_CHECK(vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &planeCount, nullptr))
        
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