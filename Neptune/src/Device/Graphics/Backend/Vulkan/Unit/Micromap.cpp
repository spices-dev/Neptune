/**
* @file Micromap.cpp.
* @brief The Micromap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Micromap.h"

namespace Neptune::Vulkan::Unit {

    Micromap::~Micromap()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyMicromapEXT(m_Device, m_Handle, GetAllocator());
    }

    void Micromap::CreateMicromap(VkDevice device, const VkMicromapCreateInfoEXT& info)
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_ASSERT(device)

        m_Device = device;

        VULKAN_CHECK(vkCreateMicromapEXT(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif