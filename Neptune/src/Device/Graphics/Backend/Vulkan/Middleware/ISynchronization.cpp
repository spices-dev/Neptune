/**
* @file ISynchronization.cpp.
* @brief The ISynchronization Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ISynchronization.h"
#include "Synchronization.h"
#include "Synchronization2.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Synchronization2.h"

namespace Neptune::Vulkan::Middleware {
	
	UP<ISynchronization> ISynchronization::Create(Context& context)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (context.Get<IExtensions>()->GetContext()->Has<Extension::ISynchronization2>())
		{
			return CreateUP<Synchronization2>();
		}

		return CreateUP<Synchronization>();
	}
}

#endif