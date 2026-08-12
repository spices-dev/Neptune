/**
* @file DebugReportCallback.cpp.
* @brief The DebugReportCallback Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DebugReportCallback.h"

namespace Neptune::Vulkan::Unit {

    DebugReportCallback::~DebugReportCallback()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyDebugReportCallbackEXT(m_Instance, m_Handle, GetAllocator());
    }

    void DebugReportCallback::CreateDebugReportCallback(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(instance);

        m_Instance = instance;

        VULKAN_CHECK(vkCreateDebugReportCallbackEXT(instance, &info, GetAllocator(), &m_Handle))
    }
}

#endif