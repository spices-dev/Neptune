/**
* @file Extensions.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/ExtensionHeader.h"

namespace Neptune::Vulkan {

	Extensions::Extensions(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create();
	}

	void Extensions::Create()
	{
		NEPTUNE_PROFILE_ZONE
	}
}

#endif