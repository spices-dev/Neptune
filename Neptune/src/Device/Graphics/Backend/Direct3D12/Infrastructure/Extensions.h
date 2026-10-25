/**
* @file Extensions.h.
* @brief The Extensions Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D12/Extension/Context.h"

namespace Neptune {
	
	class Window;
}

namespace Neptune::Direct3D12 {

	using IExtensions = IInfrastructure<class Extensions, EInfrastructure::Extensions>;

	/**
	* @brief Direct3D12::Extensions Class.
	* This class defines the Direct3D12::Extensions behaves.
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