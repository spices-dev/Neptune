/**
* @file IndirectExecutionSet.cpp.
* @brief The IndirectExecutionSet Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IndirectExecutionSet.h"

namespace Neptune::Vulkan::Unit {

    IndirectExecutionSet::~IndirectExecutionSet()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyIndirectExecutionSetEXT(m_Device, m_Handle, GetAllocator());
    }

    void IndirectExecutionSet::CreateIndirectExecutionSet(VkDevice device, const VkIndirectExecutionSetCreateInfoEXT& info)
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_ASSERT(device)

        m_Device = device;

        VULKAN_CHECK(vkCreateIndirectExecutionSetEXT(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif