/**
* @file DeferredOperation.cpp.
* @brief The DeferredOperation Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DeferredOperation.h"

namespace Neptune::Vulkan::Unit {

    DeferredOperation::~DeferredOperation()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyDeferredOperationKHR(m_Device, m_Handle, GetAllocator());
    }

    void DeferredOperation::CreateDeferredOperation(VkDevice device)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VULKAN_CHECK(vkCreateDeferredOperationKHR(device, GetAllocator(), &m_Handle))
    }
}

#endif