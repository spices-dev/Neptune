/**
* @file LayerSetting.h.
* @brief The LayerSetting Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"
#include "Vulkan/Infrastructure/InstanceTable.h"
#include "Vulkan/Unit/LayerSettingSet.h"

namespace Neptune::Vulkan::Resource {

	/**
	* @brief Vulkan::LayerSetting Class.
	* This class defines the Vulkan::LayerSetting behaves.
	*/
	class LayerSetting
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] instance InstanceTable.
		*/
		explicit LayerSetting(const InstanceTable& instance) : m_InstanceTable(&instance) {}

		/**
		* @brief Destructor Function.
		*/
		virtual ~LayerSetting() = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::LayerSettingSet::Handle& Handle() const { return m_LayerSettingSet.GetHandle(); }

		/**
		* @brief Create LayerSettingSet.
		* 
		* @param[in] name Layer Name.
		* @param[in] info VkInstanceCreateInfo.
		* @param[in] pAllocator VkAllocationCallbacks.
		*/
		void CreateLayerSettingSet(const char* name, const VkInstanceCreateInfo& info, const VkAllocationCallbacks* pAllocator);
		
		/**
		* @brief Set Setting.
		* 
		* @tparam T .
		*/
		template<typename T>
		void SetSetting(T&& t)
		{
			m_Setting = std::forward<T>(t);
		}
		
		/**
		* @brief Get Setting as template.
		* 
		* @tparam T .
		*/
		template<typename T>
		T* As()
		{
			return dynamic_cast<T*>(m_Setting.get());
		}
		
		/**
		* @brief Get Layer Setting Value.
		*
		* @param[in] name SettingName.
		* @param[out] v Out Value.
		* @param[out] defaultV default Value.
		* 
		* @return Returns VkResult.
		*/
		template<typename T>
		VkResult GetValue(const std::string& name, T& v, const T& defaultV)
		{
			auto result = m_LayerSettingSet.GetValue(name, v, defaultV);
			
			if (result != VK_SUCCESS) return result;
			
			NEPTUNE_LOG_CORE(I) << "LayerSetting: [ " << name << " ] : " << v;
			
			return VK_SUCCESS;
		}
        
		/**
		* @brief Get Layer Setting Values.
		*
		* @param[in] name SettingName.
		* @param[out] v Out Value.
		* @param[out] defaultV default Value.
		* 
		* @return Returns VkResult.
		*/
		template<typename T>
		VkResult GetValues(const std::string& name, std::vector<T>& v, const std::vector<T>& defaultV)
		{
			auto result = m_LayerSettingSet.GetValues(name, v, defaultV);
			
			if (result != VK_SUCCESS) return result;
			
			NEPTUNE_LOG_CORE(I) << "LayerSetting: [ " << name << " ] : " << v;
			
			return VK_SUCCESS;
		}
		
	private:

		const InstanceTable*  m_InstanceTable;              // @brief InstanceTable.
		Unit::LayerSettingSet m_LayerSettingSet;            // @brief This LayerSettingSet.
		SP<void*>             m_Setting;                    // @brief Setting Data.      
	};
}