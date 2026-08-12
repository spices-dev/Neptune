/**
* @file PipelineBinary.cpp.
* @brief The PipelineBinary Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "PipelineBinary.h"

namespace Neptune::Vulkan::Unit {

    PipelineBinary::~PipelineBinary()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyPipelineBinaryKHR(m_Device, m_Handle, GetAllocator());
    }

    void PipelineBinary::CreatePipelineBinary(VkDevice device, const VkPipelineBinaryCreateInfoKHR& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VkPipelineBinaryHandlesInfoKHR       handles {};
        handles.sType                      = VK_STRUCTURE_TYPE_PIPELINE_BINARY_HANDLES_INFO_KHR;
        handles.pipelineBinaryCount        = 1;
        handles.pPipelineBinaries          = &m_Handle;
        
        VULKAN_CHECK(vkCreatePipelineBinariesKHR(device, &info, GetAllocator(), &handles))
    }
}

#endif