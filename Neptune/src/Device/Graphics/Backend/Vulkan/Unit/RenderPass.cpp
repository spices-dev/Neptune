/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderPass.h"

namespace Neptune::Vulkan::Unit {

	RenderPass::~RenderPass()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyRenderPass(m_Device, m_Handle, GetAllocator());
	}

	void RenderPass::SetFunctor(PFN_vkCreateRenderPass2KHR create)
	{
		NEPTUNE_PROFILE_ZONE

		vkCreateRenderPass2KHR = create;
	}

	void RenderPass::CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(device)

		m_Device = device;

		VULKAN_CHECK(vkCreateRenderPass(device, &info, GetAllocator(), &m_Handle))
	}
	
	void RenderPass::CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;
		
		VULKAN_CHECK(vkCreateRenderPass2KHR(device, &info, GetAllocator(), &m_Handle))
	}
}

#endif