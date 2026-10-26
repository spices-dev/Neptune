/**
* @file IDescriptorList.h.
* @brief The IDescriptorList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"

namespace Neptune::Vulkan::Middleware {
	
	/**
	* @brief Interface of DescriptorList.
	*/
	class IDescriptorList
	{
	public:

		/**
		* @brief Create IDescriptorList.
		* 
		* @param context Context.
		* 
		* @return Returns IDescriptorList.
		*/
		static UP<IDescriptorList> Create(Context& context);
		
		/**
		* @brief Destructor Function.
		*/
		virtual ~IDescriptorList() = default;
	};
}

#endif