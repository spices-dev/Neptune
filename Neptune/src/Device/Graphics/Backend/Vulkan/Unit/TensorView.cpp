/**
* @file TensorView.cpp.
* @brief The TensorView Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "TensorView.h"

namespace Neptune::Vulkan::Unit {

    TensorView::~TensorView()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyTensorViewARM(m_Device, m_Handle, GetAllocator());
    }

    void TensorView::CreateTensorView(VkDevice device, const VkTensorViewCreateInfoARM& info)
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_ASSERT(device)

        m_Device = device;

        VULKAN_CHECK(vkCreateTensorViewARM(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif