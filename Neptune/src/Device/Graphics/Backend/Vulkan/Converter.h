/**
* @file Converter.h.
* @brief The Converter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core.h"
#include "Resource/Texture/RenderTarget.h"
#include "Asset/SOP/Enum.h"
#include "Resource/Shader/Shader.h"
#include "Device/Graphics/Frontend/Memory.h"

#include <vk_mem_alloc.h>

namespace Neptune::Vulkan {

	/**
	* @brief Convert TextureFormat to VkFormat.
	* 
	* @param[in] f TextureFormat.
	* 
	* @return Returns VkFormat.
	*/
	VkFormat ToVkFormat(TextureFormat f);

	/**
	* @brief Convert TextureDomain to VkImageType.
	*
	* @param[in] d TextureDomain.
	*
	* @return Returns VkImageType.
	*/
	VkImageType ToVkImageType(TextureDomain d);

	/**
	* @brief Convert TextureDomain to VkImageViewType.
	*
	* @param[in] d TextureDomain.
	*
	* @return Returns TextureDomain.
	*/
	VkImageViewType ToVkImageViewType(TextureDomain d);

	/**
	* @brief Convert RHIMemoryUsage to VkMemoryPropertyFlags.
	*
	* @param[in] m EMemory.
	*
	* @return Returns VkMemoryPropertyFlags.
	*/
	VkMemoryPropertyFlags ToVkMemoryPropertyFlags(EMemory m);

	/**
	* @brief Convert RHIMemoryUsage to VmaMemoryUsage.
	*
	* @param[in] m EMemory.
	*
	* @return Returns VmaMemoryUsage.
	*/
	VmaMemoryUsage ToVmaMemoryUsage(EMemory m);

	/**
	* @brief Convert ECullMode to VkCullModeFlags.
	*
	* @param[in] c ECullMode.
	*
	* @return Returns VkCullModeFlags.
	*/
	VkCullModeFlags ToVkCullModeFlags(ECullMode c);

	/**
	* @brief Convert ETopology to VkPrimitiveTopology.
	*
	* @param[in] t ETopology.
	*
	* @return Returns VkPrimitiveTopology.
	*/
	VkPrimitiveTopology ToVkPrimitiveTopology(ETopology t);

	/**
	* @brief Convert ShaderStage to VkShaderStageFlagBits.
	*
	* @param[in] s ShaderStage.
	*
	* @return Returns VkShaderStageFlagBits.
	*/
	VkShaderStageFlagBits ToVkShaderStageFlagBits(ShaderStage s);

	/**
	* @brief Convert AttachmentOP to VkAttachmentLoadOp.
	*
	* @param[in] op AttachmentOP.
	*
	* @return Returns VkAttachmentLoadOp.
	*/
	VkAttachmentLoadOp ToVkAttachmentLoadOp(AttachmentOP op);

	/**
	* @brief Convert AttachmentLayout to VkImageLayout.
	*
	* @param[in] l AttachmentLayout.
	*
	* @return Returns VkImageLayout.
	*/
	VkImageLayout ToVkImageLayout(AttachmentLayout l);

	/**
	* @brief Convert EPipelineAccess to VkAccessFlags2.
	*
	* @param[in] a EPipelineAccess.
	*
	* @return Returns VkAccessFlags2.
	*/
	VkAccessFlags2 ToVkAccessFlags(Graphic::EPipelineAccess a);
	
	/**
	* @brief Convert EPipelineStage to VkPipelineStageFlags2.
	*
	* @param[in] s EPipelineStage.
	*
	* @return Returns VkPipelineStageFlags2.
	*/
	VkPipelineStageFlags2 ToVkPipelineStageFlags(Graphic::EPipelineStage s);
	
	/**
	* @brief Convert VkAccessFlags2 to VkAccessFlags.
	*
	* @param[in] f VkAccessFlags2.
	*
	* @return Returns VkAccessFlags.
	*/
	VkAccessFlags ToVkAccessFlags(VkAccessFlags2 f);
	
	/**
	* @brief Convert VkPipelineStageFlags2 to VkPipelineStageFlags.
	*
	* @param[in] f VkPipelineStageFlags2.
	*
	* @return Returns VkPipelineStageFlags.
	*/
	VkPipelineStageFlags ToVkPipelineStageFlags(VkPipelineStageFlags2 f);
	
	/**
	* @brief Convert VkFormat to TextureFormat.
	*
	* @param[in] f VkFormat.
	*
	* @return Returns TextureFormat.
	*/
	TextureFormat ToTextureFormat(VkFormat f);

	/**
	* @brief Convert EBufferUsage to VkBufferUsageFlags.
	*
	* @param[in] u EBufferUsage.
	*
	* @return Returns VkBufferUsageFlags.
	*/
	VkBufferUsageFlags ToVkBufferUsageFlags(Graphic::EBufferUsage u);
	
	/**
	* @brief Convert VkMemoryHeapFlags to std::string.
	*
	* @param[in] flag VkMemoryHeapFlags.
	*
	* @return Returns std::string.
	*/
	std::string ToString(VkMemoryHeapFlags flag);
	
	/**
	* @brief Convert VkQueueFlagBits to std::string.
	*
	* @param[in] bit VkQueueFlagBits.
	*
	* @return Returns std::string.
	*/
	std::string ToString(VkQueueFlagBits bit);
	
	/**
	* @brief Convert VkPhysicalDeviceType to std::string.
	*
	* @param[in] type VkPhysicalDeviceType.
	*
	* @return Returns std::string.
	*/
	std::string ToString(VkPhysicalDeviceType type);

}

#endif