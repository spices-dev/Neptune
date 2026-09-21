/**
* @file Functions.h.
* @brief The Functions Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Infrastructure.h"

namespace Neptune::Vulkan {

	using IFunctions = IInfrastructure<class Functions, EInfrastructure::Functions>;

	/**
	* @brief Vulkan::Functions Class.
	* This class defines the Vulkan::Functions behaves.
	*/
	class Functions : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Functions(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Functions() override = default;

		/**
		* @brief LoadInstance.
		* 
		* @param[in] instance VkInstance
		*/
		void LoadInstance(VkInstance instance);

		/**
		* @brief LoadDevice.
		* 
		* @param[in] device VkDevice
		*/
		void LoadDevice(VkDevice device);
		
	private:

		/**
		* @brief Create Functions.
		*/
		void Create();
	};
	
}

#endif