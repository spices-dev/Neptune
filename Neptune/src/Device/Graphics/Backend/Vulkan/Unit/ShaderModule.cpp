/**
* @file ShaderModule.cpp.
* @brief The ShaderModule Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ShaderModule.h"

namespace Neptune::Vulkan::Unit {

    ShaderModule::~ShaderModule()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyShaderModule(m_Device, m_Handle, GetAllocator());
    }

    void ShaderModule::CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VK_CHECK(vkCreateShaderModule(device, &info, GetAllocator(), &m_Handle))
    }

}

#endif