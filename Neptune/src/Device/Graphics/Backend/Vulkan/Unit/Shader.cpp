/**
* @file Shader.cpp.
* @brief The Shader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Shader.h"

namespace Neptune::Vulkan::Unit {

	Shader::~Shader()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyShaderEXT(m_Device, m_Handle, GetAllocator());
	}

	void Shader::CreateShader(VkDevice device, const VkShaderCreateInfoEXT& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateShadersEXT(device, 1, &info, GetAllocator(), &m_Handle))
	}

}

#endif