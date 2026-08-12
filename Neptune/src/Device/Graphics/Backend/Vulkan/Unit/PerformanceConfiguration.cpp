/**
* @file PerformanceConfiguration.cpp.
* @brief The PerformanceConfiguration Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "PerformanceConfiguration.h"

namespace Neptune::Vulkan::Unit {

    PerformanceConfiguration::~PerformanceConfiguration()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkReleasePerformanceConfigurationINTEL(m_Device, m_Handle);
    }

    void PerformanceConfiguration::CreatePerformanceConfiguration(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VULKAN_CHECK(vkAcquirePerformanceConfigurationINTEL(device, &info, &m_Handle))
    }
}

#endif