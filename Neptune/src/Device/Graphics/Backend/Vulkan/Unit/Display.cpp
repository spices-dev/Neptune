/**
* @file Display.cpp.
* @brief The Display Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Display.h"

namespace Neptune::Vulkan::Unit {

    Display::~Display()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        VULKAN_CHECK(vkReleaseDisplayEXT(m_Device, m_Handle))
    }
    
    void Display::AcquireDisplay(VkPhysicalDevice physicalDevice)
    {
        NEPTUNE_PROFILE_ZONE
        
#ifdef NP_PLATFORM_LINUX
        
        //VULKAN_CHECK(VK_EXT_acquire_xlib_display(physicalDevice, drmFd, m_Handle))
        
        int32_t drmFd = 0;
        
        VULKAN_CHECK(VK_EXT_acquire_drm_display(physicalDevice, drmFd, m_Handle))
        
#elifdef NP_PLATFORM_WINDOWS
        
        VULKAN_CHECK(vkAcquireWinrtDisplayNV(physicalDevice, m_Handle))
        
#else
        
        assert(false);
        
#endif
        
    }
    
}

#endif