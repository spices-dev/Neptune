/**
* @file ValidationCache.cpp.
* @brief The ValidationCache Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ValidationCache.h"

namespace Neptune::Vulkan::Unit {

    ValidationCache::~ValidationCache()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyValidationCacheEXT(m_Device, m_Handle, GetAllocator());
    }

    void ValidationCache::CreateValidationCache(VkDevice device, const VkValidationCacheCreateInfoEXT& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VK_CHECK(vkCreateValidationCacheEXT(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif