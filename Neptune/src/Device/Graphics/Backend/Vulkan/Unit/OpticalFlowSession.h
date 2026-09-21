/**
* @file OpticalFlowSession.h.
* @brief The OpticalFlowSession Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::OpticalFlowSession Class.
	* This class defines the Vulkan::Unit::OpticalFlowSession behaves.
	*/
	class OpticalFlowSession : public Unit<VkOpticalFlowSessionNV, VkObjectType::VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		OpticalFlowSession() = default;

		/**
		* @brief Destructor Function.
		*/
		~OpticalFlowSession() override;

		/**
		* @brief Create OpticalFlowSession.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkOpticalFlowSessionCreateInfoNV.
		*/
		void CreateOpticalFlowSession(VkDevice device, const VkOpticalFlowSessionCreateInfoNV& info);

		/**
		* @brief Bind OpticalFlowSessionImage.
		*
		* @param[in] bindPoint VkOpticalFlowSessionBindingPointNV.
		* @param[in] view VkImageView.
		* @param[in] layout VkImageLayout.
		*/
		void BindOpticalFlowSessionImage(VkOpticalFlowSessionBindingPointNV bindPoint, VkImageView view, VkImageLayout layout) const;

	private:

		VkDevice                            m_Device = VK_NULL_HANDLE;            // @brief VkDevice

	};
}

#endif