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

	void Layer::BuildLayerSettingChain(std::vector<VkLayerSettingEXT>& settings)
	{
		NEPTUNE_PROFILE_ZONE

		settings.insert(settings.end(), m_Settings.begin(), m_Settings.end());
	}
}

#endif