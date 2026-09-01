/**
* @file RenderBackendInterface.cpp.
* @brief The Interface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_WINDOW_ANDROIDNATIVE

#include "RenderBackendInterface.h"

namespace Neptune::AndroidNative {

	SP<APIInterface> CreateInterface(RenderBackendEnum backend)
	{
		NEPTUNE_PROFILE_ZONE

		switch (backend)
		{
#ifdef NP_GRAPHICS_OPENGL
			case RenderBackendEnum::OpenGL:     return CreateSP<OpenGLInterface>();
#endif
			
#ifdef NP_GRAPHICS_VULKAN
			case RenderBackendEnum::Vulkan:     return CreateSP<VulkanInterface>();
#endif
			
			default:
			{
				NEPTUNE_CORE_CRITICAL("Not supported RenderBackend in Android Native Configuration.")
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