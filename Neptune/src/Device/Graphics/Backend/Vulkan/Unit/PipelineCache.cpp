/**
* @file PipelineCache.cpp.
* @brief The PipelineCache Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "PipelineCache.h"

namespace Neptune::Vulkan::Unit {

    PipelineCache::~PipelineCache()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyPipelineCache(m_Device, m_Handle, GetAllocator());
    }

    void PipelineCache::CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo& info)
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_ASSERT(device)

        m_Device = device;

        VULKAN_CHECK(vkCreatePipelineCache(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif