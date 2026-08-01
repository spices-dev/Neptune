/**
* @file Event.cpp.
* @brief The Event Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Event.h"

namespace Neptune::Vulkan::Unit {

    Event::~Event()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyEvent(m_Device, m_Handle, GetAllocator());
    }

    void Event::CreateEvent(VkDevice device, const VkEventCreateInfo& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VK_CHECK(vkCreateEvent(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif