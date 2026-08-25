/**
* @file Extensions.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/ExtensionHeader.h"
#include "Window/Window.h"

namespace Neptune::Vulkan {

	Extensions::Extensions(Context& context, EInfrastructure e, const Window* window)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create(window);
	}

	void Extensions::Create(const Window* window)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (window)
		{
			m_Context.Registry<Extension::ISwapChain>(window ? window->Extension() : std::vector{ VK_KHR_SURFACE_EXTENSION_NAME });
		}
		
		m_Context.Registry<Extension::IDeviceFault>();
	}
}

#endif