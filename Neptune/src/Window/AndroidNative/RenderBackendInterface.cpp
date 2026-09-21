/**
* @file RenderBackendInterface.cpp.
* @brief The Interface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_WINDOW_ANDROIDNATIVE

#include "RenderBackendInterface.h"

#ifdef NP_GRAPHICS_VULKAN
#include <volk.h>
#endif

namespace Neptune::AndroidNative {

	UP<APIInterface> CreateInterface(RenderBackendEnum backend)
	{
		NEPTUNE_PROFILE_ZONE

		switch (backend)
		{
#ifdef NP_GRAPHICS_OPENGL
			case RenderBackendEnum::OpenGL:     return CreateUP<OpenGLInterface>();
#endif
			
#ifdef NP_GRAPHICS_VULKAN
			case RenderBackendEnum::Vulkan:     return CreateUP<VulkanInterface>();
#endif
			
			default:
			{
				NEPTUNE_LOG_CORE(C) << "Not supported RenderBackend in Android Native Configuration.";
				return nullptr;
			}
		}
	}

#ifdef NP_GRAPHICS_VULKAN
	
	std::vector<const char*> VulkanInterface::Extension() const
	{
		NEPTUNE_PROFILE_ZONE

		std::vector<const char*> extensions;

		extensions.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME);
		extensions.emplace_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);

		return extensions;
	}
	
#endif

}

#endif