/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SwapChain.h"

namespace Neptune::Vulkan::Unit {

	SwapChain::~SwapChain()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroySwapchainKHR(m_Device, m_Handle, GetAllocator());
	}

	void SwapChain::CreateSwapchain(VkDevice device, const VkSwapchainCreateInfoKHR& createInfo)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(device && !m_Handle)

		m_Device = device;

		VULKAN_CHECK(vkCreateSwapchainKHR(m_Device, &createInfo, GetAllocator(), &m_Handle))
	}

	std::vector<VkImage> SwapChain::GetSwapchainImages() const
	{
		NEPTUNE_PROFILE_ZONE

		uint32_t imageCount = 0;

		VULKAN_CHECK(vkGetSwapchainImagesKHR(m_Device, m_Handle, &imageCount, nullptr))

		std::vector<VkImage> images(imageCount);

		VULKAN_CHECK(vkGetSwapchainImagesKHR(m_Device, m_Handle, &imageCount, images.data()))

		return images;
	}

	VkResult SwapChain::GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex) const
	{
		NEPTUNE_PROFILE_ZONE

		return vkAcquireNextImageKHR(m_Device, m_Handle, UINT64_MAX, semaphore, VK_NULL_HANDLE, &imageIndex);
	}
	
	void SwapChain::SetHdrMetadata(const VkHdrMetadataEXT& meta) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkSetHdrMetadataEXT(m_Device, 1, &m_Handle, &meta);
	}
}

#endif