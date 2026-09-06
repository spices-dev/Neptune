/**
* @file Converter.cpp.
* @brief The Converter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Converter.h"

namespace Neptune::Vulkan {

	VkFormat ToVkFormat(TextureFormat f)
	{
		NEPTUNE_PROFILE_ZONE

		switch (f)
		{
			case TextureFormat::RGBA8_UNORM:               return VkFormat::VK_FORMAT_R8G8B8A8_UNORM;
			case TextureFormat::RGBA16_SFLOAT:             return VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT;
			case TextureFormat::R8_G8B8_2PLANE_420_UNORM:  return VkFormat::VK_FORMAT_G8_B8R8_2PLANE_420_UNORM;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported Texture Format To VkFormat.";
				return VK_FORMAT_R8G8B8A8_UNORM;
			}
		}
	}

	VkImageType ToVkImageType(TextureDomain d)
	{
		NEPTUNE_PROFILE_ZONE

		switch (d)
		{
			case TextureDomain::Texture1D:      return VkImageType::VK_IMAGE_TYPE_1D;
			case TextureDomain::Texture1DArray: return VkImageType::VK_IMAGE_TYPE_1D;
			case TextureDomain::Texture2D:      return VkImageType::VK_IMAGE_TYPE_2D;
			case TextureDomain::Texture2DArray: return VkImageType::VK_IMAGE_TYPE_2D;
			case TextureDomain::Texture3D:      return VkImageType::VK_IMAGE_TYPE_3D;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported Texture Domain To VkImageType.";
				return VK_IMAGE_TYPE_1D;
			}
		}
	}

	VkImageViewType ToVkImageViewType(TextureDomain d)
	{
		NEPTUNE_PROFILE_ZONE

		switch (d)
		{
			case TextureDomain::Texture1D:      return VkImageViewType::VK_IMAGE_VIEW_TYPE_1D;
			case TextureDomain::Texture1DArray: return VkImageViewType::VK_IMAGE_VIEW_TYPE_1D_ARRAY;
			case TextureDomain::Texture2D:      return VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
			case TextureDomain::Texture2DArray: return VkImageViewType::VK_IMAGE_VIEW_TYPE_2D_ARRAY;
			case TextureDomain::Texture3D:      return VkImageViewType::VK_IMAGE_VIEW_TYPE_3D;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported Texture Domain To VkImageViewType.";
				return VK_IMAGE_VIEW_TYPE_2D;
			}
		}
	}

	VkMemoryPropertyFlags ToVkMemoryPropertyFlags(EMemory m)
	{
		NEPTUNE_PROFILE_ZONE

		switch (m)
		{
			case EMemory::Device:    return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			case EMemory::Host:      return VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
			case EMemory::Shared:    return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
			case EMemory::Other:     return VK_MEMORY_PROPERTY_PROTECTED_BIT;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported EMemory To VkMemoryPropertyFlags.";
				return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			}
		}
	}

	VmaMemoryUsage ToVmaMemoryUsage(EMemory m)
	{
		NEPTUNE_PROFILE_ZONE

		switch (m)
		{
			case EMemory::Device:    return VMA_MEMORY_USAGE_GPU_ONLY;
			case EMemory::Host:      return VMA_MEMORY_USAGE_CPU_ONLY;
			case EMemory::Shared:    return VMA_MEMORY_USAGE_CPU_TO_GPU;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported EMemory To VmaMemoryUsage.";
				return VMA_MEMORY_USAGE_GPU_ONLY;
			}
		}
	}

	VkCullModeFlags ToVkCullModeFlags(ECullMode c)
	{
		NEPTUNE_PROFILE_ZONE

		switch (c)
		{
			case ECullMode::None:    return VK_CULL_MODE_NONE;
			case ECullMode::Front:   return VK_CULL_MODE_FRONT_BIT;
			case ECullMode::Back:    return VK_CULL_MODE_BACK_BIT;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported ECullMode To VkCullModeFlags.";
				return VK_CULL_MODE_NONE;
			}
		}
	}
	
	VkPrimitiveTopology ToVkPrimitiveTopology(ETopology t)
	{
		NEPTUNE_PROFILE_ZONE

		switch (t)
		{
			case ETopology::TriangleList:     return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			case ETopology::TriangleStrip:    return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported ETopology To VkCullModeFlags.";
				return VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
			}
		}
	}

	VkShaderStageFlagBits ToVkShaderStageFlagBits(ShaderStage s)
	{
		NEPTUNE_PROFILE_ZONE

		switch (s)
		{
			case ShaderStage::Vertex:    return VK_SHADER_STAGE_VERTEX_BIT;
			case ShaderStage::Fragment:  return VK_SHADER_STAGE_FRAGMENT_BIT;
			case ShaderStage::Compute:   return VK_SHADER_STAGE_COMPUTE_BIT;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported ShaderStage To VkShaderStageFlagBits.";
				return VK_SHADER_STAGE_VERTEX_BIT;
			}
		}
	}

	VkAttachmentLoadOp ToVkAttachmentLoadOp(AttachmentOP op)
	{
		NEPTUNE_PROFILE_ZONE

		switch (op)
		{
			case AttachmentOP::Clear:    return VK_ATTACHMENT_LOAD_OP_CLEAR;
			case AttachmentOP::Load:     return VK_ATTACHMENT_LOAD_OP_LOAD;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported AttachmentOP To VkAttachmentLoadOp.";
				return VK_ATTACHMENT_LOAD_OP_CLEAR;
			}
		}
	}

	VkImageLayout ToVkImageLayout(AttachmentLayout l)
	{
		NEPTUNE_PROFILE_ZONE

		switch (l)
		{
			case AttachmentLayout::Undefined:           return VK_IMAGE_LAYOUT_UNDEFINED;
			case AttachmentLayout::ColorAttachment:     return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			case AttachmentLayout::ShaderRead:          return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported AttachmentLayout To VkImageLayout.";
				return VK_IMAGE_LAYOUT_UNDEFINED;
			}
		}
	}
	
	VkAccessFlags ToVkAccessFlags(EPipelineAccess a)
	{
		NEPTUNE_PROFILE_ZONE

		switch (a)
		{
			case EPipelineAccess::ShaderRead:           return VK_ACCESS_SHADER_READ_BIT;
			case EPipelineAccess::ShaderWrite:          return VK_ACCESS_SHADER_WRITE_BIT;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported EPipelineAccess To VkAccessFlagBits.";
				return VK_ACCESS_NONE;
			}
		}
	}
	
	VkPipelineStageFlags ToVkPipelineStageFlags(EPipelineStage s)
	{
		NEPTUNE_PROFILE_ZONE

		switch (s)
		{
			case EPipelineStage::VertexShader:           return VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
			case EPipelineStage::FragmentShader:         return VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
			case EPipelineStage::ComputeShader:          return VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported EPipelineStage To VkPipelineStageFlagBits.";
				return VK_PIPELINE_STAGE_NONE;
			}
		}
	}

	TextureFormat ToTextureFormat(VkFormat f)
	{
		NEPTUNE_PROFILE_ZONE

		switch (f)
		{
			case VkFormat::VK_FORMAT_R8G8B8A8_UNORM:                  return TextureFormat::RGBA8_UNORM;
			case VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT:             return TextureFormat::RGBA16_SFLOAT;
			case VkFormat::VK_FORMAT_G8_B8R8_2PLANE_420_UNORM:        return TextureFormat::R8_G8B8_2PLANE_420_UNORM;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported VkFormat To Texture Format.";
				return TextureFormat::RGBA8_UNORM;
			}
		}
	}

	std::string ToString(VkMemoryHeapFlags flag)
	{
		NEPTUNE_PROFILE_ZONE

		switch (flag)
		{
		case VK_MEMORY_HEAP_DEVICE_LOCAL_BIT:
			return "Device Local";
		case VK_MEMORY_HEAP_MULTI_INSTANCE_BIT:        // NOTICE THAT: enum value also represents "VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR"
			return "Multiple Instance";
		default:
			// In case that it does NOT correspond to device local memory
			return "Host Local";
		}
	}
	
	std::string ToString(VkQueueFlagBits bit)
	{
		NEPTUNE_PROFILE_ZONE
		
		switch (bit)
		{
			case VK_QUEUE_GRAPHICS_BIT:                 return "Graphic Queue";
			case VK_QUEUE_COMPUTE_BIT:                  return "Compute Queue";
			case VK_QUEUE_TRANSFER_BIT:                 return "Transfer Queue";
			case VK_QUEUE_SPARSE_BINDING_BIT:           return "Sparse Binding Queue";
			case VK_QUEUE_PROTECTED_BIT:                return "Protected Queue";
			case VK_QUEUE_VIDEO_DECODE_BIT_KHR:         return "Video Decode Queue";
			case VK_QUEUE_VIDEO_ENCODE_BIT_KHR:         return "Video Encode Queue";
			case VK_QUEUE_OPTICAL_FLOW_BIT_NV:          return "Optical Flow Queue";
			case VK_QUEUE_DATA_GRAPH_BIT_ARM:           return "Data Graph Queue";
			default:                                    return "NonNamed";
		}
	}
}

#endif