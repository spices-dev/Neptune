/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

#include <vector>

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::SwapChain Class.
	* This class defines the Vulkan::Unit::SwapChain behaves.
	*/
	class SwapChain : public Unit<VkSwapchainKHR, VkObjectType::VK_OBJECT_TYPE_SWAPCHAIN_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		SwapChain() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~SwapChain() override;

		/**
		* @brief Set Functor.
		* 
		* @param[in] setHdrMetadata PFN_vkSetHdrMetadataEXT.
		*/
		void SetFunctor(PFN_vkSetHdrMetadataEXT setHdrMetadata);
		
		/**
		* @brief Create Swapchain.
		*
		* @param[in] device VkDevice.
		* @param[in] createInfo VkSwapchainCreateInfoKHR.
		*/
		void CreateSwapchain(VkDevice device, const VkSwapchainCreateInfoKHR& createInfo);

		/**
		* @brief Get SwapchainImages.
		* 
		* @return Returns SwapchainImages.
		*/
		std::vector<VkImage> GetSwapchainImages() const;

		/**
		* @brief Get next SwapchainImage.
		*
		* @param[in] semaphore VkSemaphore.
		* @param[out] imageIndex .
		*
		* @return Returns VkResult.
		*/
		VkResult GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex) const;

		/**
		* @brief Set HDR Metadata.
		*
		* @param[in] meta VkHdrMetadataEXT.
		*/
		void SetHdrMetadata(const VkHdrMetadataEXT& meta) const;
		
	private:

		VkDevice m_Device = nullptr;                  // @brief VkDevice.
		PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT;  // @brief PFN_vkCreateOpticalFlowSessionNV
	};
}

#endif