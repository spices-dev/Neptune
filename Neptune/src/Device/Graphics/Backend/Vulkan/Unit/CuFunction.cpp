/**
* @file CuFunction.cpp.
* @brief The CuFunction Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "CuFunction.h"

namespace Neptune::Vulkan::Unit {

    CuFunction::~CuFunction()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyCuFunctionNVX(m_Device, m_Handle, GetAllocator());
    }

    void CuFunction::CreateCuFunction(VkDevice device, const VkCuFunctionCreateInfoNVX& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VULKAN_CHECK(vkCreateCuFunctionNVX(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif