/**
* @file Tensor.cpp.
* @brief The Tensor Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Tensor.h"

namespace Neptune::Vulkan::Unit {

    Tensor::~Tensor()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyTensorARM(m_Device, m_Handle, GetAllocator());
    }

    void Tensor::CreateTensor(VkDevice device, const VkTensorCreateInfoARM& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VK_CHECK(vkCreateTensorARM(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif