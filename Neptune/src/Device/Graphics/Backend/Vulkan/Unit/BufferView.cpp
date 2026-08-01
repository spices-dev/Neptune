/**
* @file BufferView.cpp.
* @brief The BufferView Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "BufferView.h"

namespace Neptune::Vulkan::Unit {

    BufferView::~BufferView()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyBufferView(m_Device, m_Handle, GetAllocator());
    }

    void BufferView::CreateBufferView(VkDevice device, const VkBufferViewCreateInfo& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VK_CHECK(vkCreateBufferView(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif