/**
* @file VideoSessionParameters.cpp.
* @brief The VideoSessionParameters Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "VideoSessionParameters.h"

namespace Neptune::Vulkan::Unit {

	VideoSessionParameters::~VideoSessionParameters()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyVideoSessionParametersKHR(m_Device, m_Handle, GetAllocator());
	}

	void VideoSessionParameters::CreateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersCreateInfoKHR& createInfo)
	{
		NEPTUNE_PROFILE_ZONE
			
		NEPTUNE_ASSERT(device && !m_Handle)

		m_Device = device;

		VULKAN_CHECK(vkCreateVideoSessionParametersKHR(m_Device, &createInfo, GetAllocator(), &m_Handle))
	}

	void VideoSessionParameters::UpdateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersUpdateInfoKHR& updateInfo) const
	{
		NEPTUNE_PROFILE_ZONE

		VULKAN_CHECK(vkUpdateVideoSessionParametersKHR(m_Device, m_Handle, &updateInfo))
	}
}

#endif