/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Surface.h"

namespace Neptune::Vulkan::Display {

	/**
	* @brief Vulkan::Display::Surface Class.
	* This class defines the Vulkan::Display::Surface behaves.
	*/
	class Surface : public Vulkan::Surface
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] implement WindowImplement.
		*/
		Surface(Context& context, EInfrastructure e, WindowImplement implement);

		/**
		* @brief Destructor Function.
		*/
		~Surface() override = default;

		/**
		* @brief Create Surface.
		* 
		* @param[in] physicalDevice
		* 
		* @return Returns true if succeeded.
		*/
		bool Create(VkPhysicalDevice physicalDevice);

	};
	
}

#endif