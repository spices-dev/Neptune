/**
* @file VideoSessionParameters.h.
* @brief The VideoSessionParameters Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::VideoSessionParameters Class.
	* This class defines the Vulkan::Unit::VideoSessionParameters behaves.
	*/
	class VideoSessionParameters : public Unit<VkVideoSessionParametersKHR, VkObjectType::VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		VideoSessionParameters() = default;

		/**
		* @brief Destructor Function.
		*/
		~VideoSessionParameters() override;

		/**
		* @brief Create VideoSessionParameters.
		*
		* @param[in] device VkDevice.
		* @param[in] createInfo VkVideoSessionParametersCreateInfoKHR.
		*/
		void CreateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersCreateInfoKHR& createInfo);

		/**
		* @brief Update VideoSessionParameters.
		*
		* @param[in] device VkDevice.
		* @param[in] updateInfo VkVideoSessionParametersUpdateInfoKHR.
		*/
		void UpdateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersUpdateInfoKHR& updateInfo) const;

	private:

		VkDevice m_Device = VK_NULL_HANDLE; // @brief VkDevice.
	};
}

#endif