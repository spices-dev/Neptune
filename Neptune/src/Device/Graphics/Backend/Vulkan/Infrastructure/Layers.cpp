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
		
		m_Context.Registry<Layer::IApiDump>                   (Layer::ELayerState::Extent);
		m_Context.Registry<Layer::ICrashDiagnostic>           (Layer::ELayerState::Extent);
		m_Context.Registry<Layer::IGfxReconstruct>            (Layer::ELayerState::Extent);
		m_Context.Registry<Layer::IMonitor>                   (Layer::ELayerState::Extent);
		m_Context.Registry<Layer::IScreenShot>                (Layer::ELayerState::Extent);
		m_Context.Registry<Layer::IValidation>                (Layer::ELayerState::Extent);
		m_Context.Registry<Layer::IProfiles>                  (Layer::ELayerState::Extent);
		m_Context.Registry<Layer::IShaderObject>              (Layer::ELayerState::Extent);
		m_Context.Registry<Layer::ISynchronization2>          (Layer::ELayerState::Extent);
	}
}

#endif