/**
* @file DescriptorUpdateTemplate.cpp.
* @brief The DescriptorUpdateTemplate Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DescriptorUpdateTemplate.h"

namespace Neptune::Vulkan::Unit {

    DescriptorUpdateTemplate::~DescriptorUpdateTemplate()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyDescriptorUpdateTemplate(m_Device, m_Handle, GetAllocator());
    }

    void DescriptorUpdateTemplate::CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VK_CHECK(vkCreateDescriptorUpdateTemplate(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif