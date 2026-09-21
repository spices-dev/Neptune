/**
* @file Functions.cpp.
* @brief The Functions Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Functions.h"
#include "Instance.h"

#define VOLK_IMPLEMENTATION
#include <volk.h>

namespace Neptune::Vulkan {

	Functions::Functions(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE
		
		Create();
	}

	void Functions::Create()
	{
		NEPTUNE_PROFILE_ZONE

		VULKAN_CHECK(volkInitialize())
	}

	void Functions::LoadInstance(VkInstance instance)
	{
		NEPTUNE_PROFILE_ZONE

		volkLoadInstance(instance);
	}

	void Functions::LoadDevice(VkDevice device)
	{
		NEPTUNE_PROFILE_ZONE
		
		volkLoadDevice(device);
	}
}

#endif