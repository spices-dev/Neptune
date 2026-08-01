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

    void DebugUtilsMessenger::SetFunctor(PFN_vkCreateDebugUtilsMessengerEXT create, PFN_vkDestroyDebugUtilsMessengerEXT destroy)
    {
        NEPTUNE_PROFILE_ZONE
        
        vkCreateDebugUtilsMessengerEXT  = create;
        vkDestroyDebugUtilsMessengerEXT = destroy;
    }
    
    void DebugUtilsMessenger::CreateDebugUtilsMessenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(instance);

        m_Instance = instance;

        VK_CHECK(vkCreateDebugUtilsMessengerEXT(instance, &info, GetAllocator(), &m_Handle))
    }
}

#endif