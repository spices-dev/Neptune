/**
* @file DebugUtilsMessenger.cpp.
* @brief The DebugUtilsMessenger Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DebugUtilsMessenger.h"

namespace Neptune::Vulkan::Unit {

    DebugUtilsMessenger::~DebugUtilsMessenger()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyDebugUtilsMessengerEXT(m_Instance, m_Handle, GetAllocator());
    }
    
    void DebugUtilsMessenger::CreateDebugUtilsMessenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT& info)
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_ASSERT(instance)

        m_Instance = instance;

        VULKAN_CHECK(vkCreateDebugUtilsMessengerEXT(instance, &info, GetAllocator(), &m_Handle))
    }
}

#endif