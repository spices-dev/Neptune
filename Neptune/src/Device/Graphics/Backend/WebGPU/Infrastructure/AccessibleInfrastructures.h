/**
* @file AccessibleInfrastructures.h.
* @brief The AccessibleInfrastructures Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::WebGPU {

	using IAccessibleInfrastructures = IInfrastructure<class AccessibleInfrastructures, EInfrastructure::AccessibleInfrastructures>;

	/**
	* @brief WebGPU::AccessibleInfrastructures Class.
	* This class defines the WebGPU::AccessibleInfrastructures behaves.
	*/
	class AccessibleInfrastructures : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		AccessibleInfrastructures(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~AccessibleInfrastructures() override = default;
		
		/**
		* @brief Get Extension::EContext.
		*
		* @return Returns Extension::EContext.
		*/
		SP<AContext> GetContext() { return m_Context; }

	private:

		/**
		* @brief Create CommandBuffer.
		*/
		void Create();

	private:

		SP<AContext> m_Context;  // @brief This AContext.

	};

}

#endif