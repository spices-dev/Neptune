/**
* @file InstanceTable.h.
* @brief The InstanceTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Vulkan/Unit/Instance.h"

#include <vector>

namespace Neptune::Vulkan {

	using IInstanceTable = IInfrastructure<class InstanceTable, 0u>;
	
	/**
	* @brief Vulkan::InstanceTable Class.
	* This class defines the Vulkan::InstanceTable behaves.
	*/
	class InstanceTable : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] instance Unit::Instance.
		*/
		InstanceTable(const SP<Unit::Instance>& instance) : m_Instance(instance) {}

		/**
		* @brief Destructor Function.
		*/
		~InstanceTable() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Instance::Handle& Handle() const { return m_Instance->GetHandle(); }

	private:

		SP<Unit::Instance>               m_Instance;                    // @brief this unit Instance.

	public:
		
		PFN_vkGetInstanceProcAddr        vkGetInstanceProcAddr;         // @brief PFN_vkGetInstanceProcAddr.
		PFN_vkCreateDevice               vkCreateDevice;                // @brief PFN_vkCreateDevice.
		PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;  // @brief PFN_vkSubmitDebugUtilsMessageEXT.
	};

}