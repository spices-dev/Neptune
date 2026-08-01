/**
* @file IndirectCommandsLayout.cpp.
* @brief The IndirectCommandsLayout Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IndirectCommandsLayout.h"

namespace Neptune::Vulkan::Unit {

    IndirectCommandsLayout::~IndirectCommandsLayout()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyIndirectCommandsLayoutEXT(m_Device, m_Handle, GetAllocator());
    }

    void IndirectCommandsLayout::CreateIndirectCommandsLayout(VkDevice device, const VkIndirectCommandsLayoutCreateInfoEXT& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VK_CHECK(vkCreateIndirectCommandsLayoutEXT(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif