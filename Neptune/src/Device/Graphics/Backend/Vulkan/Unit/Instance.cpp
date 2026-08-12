/**
* @file Instance.cpp.
* @brief The Instance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Instance.h"

namespace Neptune::Vulkan::Unit {

	Instance::~Instance()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyInstance(m_Handle, GetAllocator());
	}

	void Instance::CreateInstance(const VkInstanceCreateInfo& createInfo)
	{
		NEPTUNE_PROFILE_ZONE

		assert(!m_Handle);

		VULKAN_CHECK(vkCreateInstance(&createInfo, GetAllocator(), &m_Handle))
	}
}

#endif