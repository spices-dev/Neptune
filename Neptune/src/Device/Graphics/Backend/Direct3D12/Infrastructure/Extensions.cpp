/**
* @file Extensions.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Extensions.h"
#include "Device/Graphics/Backend/Direct3D12/Extension/ExtensionHeader.h"
#include "Window/Window.h"

namespace Neptune::Direct3D12 {

	Extensions::Extensions(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create();
	}

	void Extensions::Create()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Context = CreateSP<Extension::EContext<EExtension>>();
		
		m_Context->Registry<Extension::IRenderPass>(Extension::EExtensionState::Extent);
	}
}

#endif