/**
* @file Extensions.h.
* @brief The Extensions Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Extension/Context.h"

namespace Neptune::WebGPU {

	using IExtensions = IInfrastructure<class Extensions, EInfrastructure::Extensions>;

	/**
	* @brief WebGPU::Extensions Class.
	* This class defines the WebGPU::Extensions behaves.
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
		
		/**
		* @brief Get Extension::EContext.
		* 
		* @return Returns Extension::EContext.
		*/
		const SP<Extension::EContext<EExtension>>& GetContext() const { return m_Context; }
		
		/**
		* @brief Get Extension::EContext.
		*
		* @return Returns Extension::EContext.
		*/
		SP<Extension::EContext<EExtension>>& GetContext() { return m_Context; }

    private:
        
        /**
        * @brief Create Extension.
        */
        void Create();
		
    private:
    
        SP<Extension::EContext<EExtension>> m_Context; // @brief This EContext.
	};
	
}

#endif