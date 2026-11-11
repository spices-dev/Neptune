/**
* @file IDescriptorList.h.
* @brief The IDescriptorList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Middleware {
	
	/**
	* @brief Interface of DescriptorList.
	*/
	class IDescriptorList : public Middleware
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
		~IDescriptorList() override = default;
	};
}

#endif