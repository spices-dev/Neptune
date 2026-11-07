/**
* @file Converter.cpp.
* @brief The Converter Class Implementation.
* @author Spices.
*/
#include "Converter.h"

namespace Neptune::Vulkan {

	uint32_t ToSize(VkFormat f)
	{
		switch (f)
		{
			case VK_FORMAT_R8G8B8A8_UNORM      : return 32u;
			case VK_FORMAT_R8G8B8A8_UINT       : return 32u;
			case VK_FORMAT_B8G8R8A8_UNORM      : return 32u;
			case VK_FORMAT_B8G8R8A8_UINT       : return 32u;
			case VK_FORMAT_R16G16B16A16_SFLOAT : return 64u;
			default:
			{
				NEPTUNE_LOG_CORE(E) <<  "Unsupported VkFormat To Size.";
				return VK_FORMAT_R8G8B8A8_UNORM;
			}
		}
	}
	
}