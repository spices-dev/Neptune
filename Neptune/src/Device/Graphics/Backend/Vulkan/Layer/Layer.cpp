/**
* @file Layer.cpp.
* @brief The Layer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Layer.h"

namespace Neptune::Vulkan::Layer {

	void Layer::AddLayerSetting(const VkLayerSettingEXT& setting)
	{
		NEPTUNE_PROFILE_ZONE

		m_Settings.emplace_back(setting);
	}
	
	void Layer::AddLayerSetting(const char* name, const VkBool32& data)
	{
		NEPTUNE_PROFILE_ZONE
		
		VkLayerSettingEXT                    settings {};
		settings.pLayerName                = GetInstanceLayer().c_str();
		settings.pSettingName              = name;
		settings.type                      = VK_LAYER_SETTING_TYPE_BOOL32_EXT;
		settings.valueCount                = 1;
		settings.pValues                   = &data;
		
		AddLayerSetting(settings);
	}
	
	void Layer::AddLayerSetting(const char* name, const char* data)
	{
		NEPTUNE_PROFILE_ZONE
		
		VkLayerSettingEXT                    settings {};
		settings.pLayerName                = GetInstanceLayer().c_str();
		settings.pSettingName              = name;
		settings.type                      = VK_LAYER_SETTING_TYPE_STRING_EXT;
		settings.valueCount                = 1;
		settings.pValues                   = static_cast<void*>(&data);
		
		AddLayerSetting(settings);
	}
	
	void Layer::AddLayerSetting(const char* name, const int64_t& data)
	{
		NEPTUNE_PROFILE_ZONE
		
		VkLayerSettingEXT                    settings {};
		settings.pLayerName                = GetInstanceLayer().c_str();
		settings.pSettingName              = name;
		settings.type                      = VK_LAYER_SETTING_TYPE_INT64_EXT;
		settings.valueCount                = 1;
		settings.pValues                   = &data;
		
		AddLayerSetting(settings);
	}

	void Layer::BuildLayerSettingChain(std::vector<VkLayerSettingEXT>& settings)
	{
		NEPTUNE_PROFILE_ZONE

		settings.insert(settings.end(), m_Settings.begin(), m_Settings.end());
	}
}

#endif