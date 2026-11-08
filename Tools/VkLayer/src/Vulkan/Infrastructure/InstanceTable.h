/**
* @file InstanceTable.h.
* @brief The InstanceTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"
#include "Infrastructure.h"
#include "MultiInstance.h"
#include "Vulkan/Unit/Instance.h"
#include "Vulkan/Resource/LayerSetting.h"

#include <vulkan/utility/vk_dispatch_table.h>

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
		
		UP<Unit::Instance>            m_Instance;  // @brief This Unit Instance.
		UP<Resource::LayerSetting>    m_Setting;   // @brief This Resource LayerSetting.
		VkuInstanceDispatchTable_     m_Table;     // @brief VkuInstanceDispatchTable_.
	};

}