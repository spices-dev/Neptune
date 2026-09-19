/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::RenderPass Class.
	* This class defines the Vulkan::Unit::RenderPass behaves.
	*/
	class RenderPass : public Unit<VkRenderPass, VkObjectType::VK_OBJECT_TYPE_RENDER_PASS>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		RenderPass() = default;

		/**
		* @brief Destructor Function.
		*/
		~RenderPass() override;

		/**
		* @brief Create RenderPass.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkRenderPassCreateInfo.
		*/
		void CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo& info);
		
		/**
		* @brief Create RenderPass2.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkRenderPassCreateInfo2.
		*/
		void CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;                                  // @brief VkDevice.
		PFN_vkCreateRenderPass2KHR vkCreateRenderPass2KHR = VK_NULL_HANDLE;  // @brief PFN_vkCreateRenderPass2KHR.
	};
}

#endif