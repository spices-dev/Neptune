/**
* @file InstanceTable.h.
* @brief The InstanceTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "MultiInstance.h"
#include "Vulkan/Unit/Instance.h"

namespace Neptune::Vulkan {

	using IInstanceTable = IInfrastructure<MultiInstance<void*, class InstanceTable>, 0u>;
	
	/**
	* @brief Vulkan::InstanceTable Class.
	* This class defines the Vulkan::InstanceTable behaves.
	*/
	class InstanceTable : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		InstanceTable() = default;

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

	public:
		
		UP<Unit::Instance>               m_Instance;                    // @brief this unit Instance.
		PFN_vkGetInstanceProcAddr        vkGetInstanceProcAddr;         // @brief PFN_vkGetInstanceProcAddr.
		PFN_vkCreateDevice               vkCreateDevice;                // @brief PFN_vkCreateDevice.
		PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;  // @brief PFN_vkSubmitDebugUtilsMessageEXT.
	};

}