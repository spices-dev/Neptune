/**
* @file AccelerationStructure.cpp.
* @brief The AccelerationStructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "AccelerationStructure.h"

namespace Neptune::Vulkan::Unit {

    AccelerationStructure::~AccelerationStructure()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyAccelerationStructureKHR(m_Device, m_Handle, GetAllocator());
    }

    void AccelerationStructure::CreateAccelerationStructure(VkDevice device, const VkAccelerationStructureCreateInfoKHR& info)
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_ASSERT(device)

        m_Device = device;

        VULKAN_CHECK(vkCreateAccelerationStructureKHR(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif