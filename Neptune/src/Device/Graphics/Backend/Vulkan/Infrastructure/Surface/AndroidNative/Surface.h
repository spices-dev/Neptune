/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once

#if defined(NP_GRAPHICS_VULKAN) && defined(NP_WINDOW_ANDROIDNATIVE)

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Surface.h"

namespace Neptune::Vulkan::AndroidNative {

	/**
	* @brief Vulkan::AndroidNative::Surface Class.
	* This class defines the Vulkan::AndroidNative::Surface behaves.
	*/
	class Surface : public Vulkan::Surface
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] window Native window.
		*/
		Surface(Context& context, EInfrastructure e, void* window);

		/**
		* @brief Destructor Function.
		*/
		~Surface() override = default;

	private:

		/**
		* @brief Create Surface.
		*
		* @param[in] window Native window.
		*/
		void Create(void* window);

	};
	
}

#endif
