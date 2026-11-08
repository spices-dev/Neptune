/**
* @file Converter.h.
* @brief The Converter Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core.h"

namespace Neptune::Vulkan {

	/**
	* @brief Convert VkFormat to size.
	* 
	* @param[in] f VkFormat.
	* 
	* @return Returns size.
	*/
	uint32_t ToSize(VkFormat f);

}