/**
* @file CuModule.cpp.
* @brief The CuModule Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "CuModule.h"

namespace Neptune::Vulkan::Unit {

    CuModule::~CuModule()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyCuModuleNVX(m_Device, m_Handle, GetAllocator());
    }

    void CuModule::CreateCuModule(VkDevice device, const VkCuModuleCreateInfoNVX& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VK_CHECK(vkCreateCuModuleNVX(device, &info, GetAllocator(), &m_Handle))
    }
}

#endif