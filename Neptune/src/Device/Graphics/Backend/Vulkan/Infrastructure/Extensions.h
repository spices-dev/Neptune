/**
* @file Extensions.h.
* @brief The Extensions Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Context.h"

namespace Neptune::Vulkan {

	using IExtensions = IInfrastructure<class Extensions, EInfrastructure::Extensions>;

	/**
	* @brief Vulkan::Extensions Class.
	* This class defines the Vulkan::Extensions behaves.
	*/
	class Extensions : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Extensions(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Extensions() override = default;
		
    private:
        
        /**
        * @brief Create Extension.
        */
        void Create();
		
    private:
    
        Extension::EContext<EExtension> m_Context; // @brief This EContext.
		
	};
	
}

#endif