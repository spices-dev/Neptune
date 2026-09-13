/**
* @file GpaSession.cpp.
* @brief The GpaSession Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GpaSession.h"

namespace Neptune::Vulkan::Unit {

    GpaSession::~GpaSession()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyGpaSessionAMD(m_Device, m_Handle, GetAllocator());
    }

    void GpaSession::CreateGpaSession(VkDevice device, const VkGpaSessionCreateInfoAMD& info)
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_ASSERT(device)

        m_Device = device;

        VULKAN_CHECK(vkCreateGpaSessionAMD(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif