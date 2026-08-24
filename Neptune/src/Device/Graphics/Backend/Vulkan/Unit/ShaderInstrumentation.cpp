/**
* @file ShaderInstrumentation.cpp.
* @brief The ShaderInstrumentation Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ShaderInstrumentation.h"

namespace Neptune::Vulkan::Unit {

    ShaderInstrumentation::~ShaderInstrumentation()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        vkDestroyShaderInstrumentationARM(m_Device, m_Handle, GetAllocator());
    }

    void ShaderInstrumentation::CreateShaderInstrumentation(VkDevice device, const VkShaderInstrumentationCreateInfoARM& info)
    {
        NEPTUNE_PROFILE_ZONE

        assert(device);

        m_Device = device;

        VULKAN_CHECK(vkCreateShaderInstrumentationARM(device, &info, GetAllocator(), &m_Handle))
    }

}

#endif