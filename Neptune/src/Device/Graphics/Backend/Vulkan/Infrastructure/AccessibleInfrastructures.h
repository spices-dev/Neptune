/**
* @file AccessibleInfrastructures.h.
* @brief The AccessibleInfrastructures Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::Vulkan {

	using IAccessibleInfrastructures = IInfrastructure<class AccessibleInfrastructures, EInfrastructure::AccessibleInfrastructures>;

	/**
	* @brief Vulkan::AccessibleInfrastructures Class.
	* This class defines the Vulkan::AccessibleInfrastructures behaves.
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