/**
* @file OpticalFlowSession.cpp.
* @brief The OpticalFlowSession Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "OpticalFlowSession.h"

namespace Neptune::Vulkan::Unit {

	void OpticalFlowSession::SetFunctor(PFN_vkCreateOpticalFlowSessionNV create, PFN_vkDestroyOpticalFlowSessionNV destroy, PFN_vkBindOpticalFlowSessionImageNV bind)
	{
		NEPTUNE_PROFILE_ZONE

		vkCreateOpticalFlowSessionNV    = create;
		vkDestroyOpticalFlowSessionNV   = destroy;
		vkBindOpticalFlowSessionImageNV = bind;
	}	

	OpticalFlowSession::~OpticalFlowSession()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyOpticalFlowSessionNV(m_Device, m_Handle, GetAllocator());
	}

	void OpticalFlowSession::CreateOpticalFlowSession(VkDevice device, const VkOpticalFlowSessionCreateInfoNV& info)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(device)

		m_Device = device;

		VULKAN_CHECK(vkCreateOpticalFlowSessionNV(m_Device, &info, GetAllocator(), &m_Handle))
	}

	void OpticalFlowSession::BindOpticalFlowSessionImage(VkOpticalFlowSessionBindingPointNV bindPoint, VkImageView view, VkImageLayout layout) const
	{
		NEPTUNE_PROFILE_ZONE

		VULKAN_CHECK(vkBindOpticalFlowSessionImageNV(m_Device, m_Handle, bindPoint, view, layout))
	}

}

#endif