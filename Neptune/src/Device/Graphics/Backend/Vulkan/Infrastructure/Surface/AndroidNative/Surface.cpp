/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#if defined(NP_GRAPHICS_VULKAN) && defined(NP_WINDOW_ANDROIDNATIVE)

#include "Surface.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Instance.h"

#include <android/native_window.h>

namespace Neptune::Vulkan::AndroidNative {

	Surface::Surface(Context& context, EInfrastructure e, void* window)
		: Vulkan::Surface(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create(window);
	}

	void Surface::Create(void* window)
	{
		NEPTUNE_PROFILE_ZONE

		const auto instance = GetContext().Get<IInstance>()->Handle();

		Unit::Surface::Handle handle;

		VkAndroidSurfaceCreateInfoKHR        surfaceInfo{};
		surfaceInfo.sType                  = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.window                 = static_cast<ANativeWindow*>(window);

		VULKAN_CHECK(vkCreateAndroidSurfaceKHR(instance, &surfaceInfo, GetAllocator(), &handle))

		m_Surface.SetHandle(handle);

		m_Surface.SetInstance(instance);
	}

}

#endif
