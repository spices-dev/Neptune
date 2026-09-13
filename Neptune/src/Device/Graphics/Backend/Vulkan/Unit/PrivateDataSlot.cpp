/**
* @file PrivateDataSlot.cpp.
* @brief The PrivateDataSlot Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "PrivateDataSlot.h"

namespace Neptune::Vulkan::Unit {

    PrivateDataSlot::~PrivateDataSlot()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyPrivateDataSlot(m_Device, m_Handle, GetAllocator());
    }

    void PrivateDataSlot::CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo& info)
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_ASSERT(device)

        m_Device = device;

        VULKAN_CHECK(vkCreatePrivateDataSlot(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif