/**
* @file DataGraphPipelineSession.cpp.
* @brief The DataGraphPipelineSession Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DataGraphPipelineSession.h"

namespace Neptune::Vulkan::Unit {

    DataGraphPipelineSession::~DataGraphPipelineSession()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyDataGraphPipelineSessionARM(m_Device, m_Handle, GetAllocator());
    }

    void DataGraphPipelineSession::CreateDataGraphPipelineSession(VkDevice device, const VkDataGraphPipelineSessionCreateInfoARM& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VULKAN_CHECK(vkCreateDataGraphPipelineSessionARM(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif