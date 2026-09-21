/**
* @file VideoSessionParameters.h.
* @brief The VideoSessionParameters Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

#include <vector>

namespace Neptune::Vulkan::Unit {

	constexpr uint32_t MAX_BOUND_MEMORY = 16;

	/**
	* @brief Vulkan::Unit::VideoSession Class.
	* This class defines the Vulkan::Unit::VideoSession behaves.
	*/
	class VideoSession : public Unit<VkVideoSessionKHR, VkObjectType::VK_OBJECT_TYPE_VIDEO_SESSION_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		VideoSession() = default;

		/**
		* @brief Destructor Function.
		*/
		~VideoSession() override;

		/**
		* @brief Create VideoSession.
		*
		* @param[in] device VkDevice.
		* @param[in] createInfo VkVideoSessionCreateInfoKHR.
		*/
		void CreateVideoSession(VkDevice device, const VkVideoSessionCreateInfoKHR& createInfo);

		/**
		* @brief Allocate Memory.
		*
		* @param[in] info VkMemoryAllocateInfo.
		* @param[in] flags VkMemoryPropertyFlags.
		* 
		* @return Returns VkDeviceMemory.
		*/
		VkDeviceMemory AllocateMemory(const VkMemoryAllocateInfo& info, VkMemoryPropertyFlags flags);

		/**
		* @brief Bind VideoSession Memory.
		*
		* @param[in] infos VkBindVideoSessionMemoryInfoKHR.
		*/
		void BindVideoSessionMemory(const std::vector<VkBindVideoSessionMemoryInfoKHR>& infos) const;

	private:

		VkDevice                              m_Device = VK_NULL_HANDLE;                        // @brief VkDevice.
		std::vector<VkDeviceMemory>           m_Memories{};                                     // @brief VkDeviceMemory.
		VkMemoryPropertyFlags                 m_Flags;                                          // @brief VkMemoryPropertyFlags.
	};
}

#endif