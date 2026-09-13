/**
* @file SamplerYcbcrConversion.cpp.
* @brief The SamplerYcbcrConversion Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SamplerYcbcrConversion.h"

namespace Neptune::Vulkan::Unit {

	SamplerYcbcrConversion::~SamplerYcbcrConversion()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroySamplerYcbcrConversion(m_Device, m_Handle, GetAllocator());
	}

	void SamplerYcbcrConversion::CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(device)

		m_Device = device;

		VULKAN_CHECK(vkCreateSamplerYcbcrConversion(device, &info, GetAllocator(), &m_Handle))
	}

}

#endif