/**
* @file DisplayMode.cpp.
* @brief The DisplayMode Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DisplayMode.h"

namespace Neptune::Vulkan::Unit {

    DisplayMode::~DisplayMode() = default;

    void DisplayMode::CreateDisplayMode(VkPhysicalDevice device, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VULKAN_CHECK(vkCreateDisplayModeKHR(device, display, &info, GetAllocator(), &m_Handle))
    }
}

#endif