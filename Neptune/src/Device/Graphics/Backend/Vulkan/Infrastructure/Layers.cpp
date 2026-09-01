/**
* @file Layers.cpp.
* @brief The Layers Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Layers.h"
#include "Device/Graphics/Backend/Vulkan/Layer/LayerHeader.h"

namespace Neptune::Vulkan {

	Layers::Layers(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create();
	}

	void Layers::Create()
	{
		NEPTUNE_PROFILE_ZONE
		
#ifdef NEPTUNE_DEBUG

		m_Context.Registry<Layer::IValidation>(Layer::ELayerState::Extent);

#endif

	}

	void Layers::BuildLayerSettingChain(std::vector<VkLayerSettingEXT>& settings)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Context.View([&](const auto e, const auto& layer) {
			
			layer->BuildLayerSettingChain(settings);
		});
	}
}

#endif