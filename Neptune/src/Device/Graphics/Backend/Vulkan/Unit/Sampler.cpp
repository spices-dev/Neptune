/**
* @file Sampler.cpp.
* @brief The Sampler Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Sampler.h"

namespace Neptune::Vulkan::Unit {

	Sampler::~Sampler()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroySampler(m_Device, m_Handle, GetAllocator());
	}

	void Sampler::CreateSampler(VkDevice device, const VkSamplerCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VULKAN_CHECK(vkCreateSampler(device, &info, GetAllocator(), &m_Handle))
	}
}

#endif