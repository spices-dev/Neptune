/**
* @file DebugUtilsObject.cpp.
* @brief The DebugUtilsObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DebugUtilsObject.h"
#include "Device.h"

namespace Neptune::Vulkan {

	DebugUtilsObject::DebugUtilsObject(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

	void DebugUtilsObject::BeginLabel(VkCommandBuffer cmdBuffer, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

		VkDebugUtilsLabelEXT             labelInfo{};
		labelInfo.sType                = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName           = caption.c_str();

		vkCmdBeginDebugUtilsLabelEXT(cmdBuffer, &labelInfo);
	}

	void DebugUtilsObject::EndLabel(VkCommandBuffer cmdBuffer) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdEndDebugUtilsLabelEXT(cmdBuffer);
	}

	void DebugUtilsObject::InsertLabel(VkCommandBuffer cmdBuffer, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

		VkDebugUtilsLabelEXT         labelInfo{};
		labelInfo.sType            = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName       = caption.c_str();

		vkCmdInsertDebugUtilsLabelEXT(cmdBuffer, &labelInfo);
	}

	void DebugUtilsObject::BeginQueueLabel(VkQueue queue, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

		VkDebugUtilsLabelEXT        labelInfo{};
		labelInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName      = caption.c_str();

		vkQueueBeginDebugUtilsLabelEXT(queue, &labelInfo);
	}

	void DebugUtilsObject::EndQueueLabel(VkQueue queue) const
	{
		NEPTUNE_PROFILE_ZONE

		vkQueueEndDebugUtilsLabelEXT(queue);
	}

	void DebugUtilsObject::InsertQueueLabel(VkQueue queue, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

		VkDebugUtilsLabelEXT        labelInfo{};
		labelInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName      = caption.c_str();

		vkQueueInsertDebugUtilsLabelEXT(queue, &labelInfo);
	}
}

#endif