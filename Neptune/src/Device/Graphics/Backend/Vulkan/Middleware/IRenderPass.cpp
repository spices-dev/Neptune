/**
* @file IRenderPass.cpp.
* @brief The IRenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IRenderPass.h"
#include "RenderPass.h"
#include "RenderPass2.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DynamicRendering.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"

namespace Neptune::Vulkan::Middleware {
	
	UP<IRenderPass> IRenderPass::Create(Context& context)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (context.Get<IExtensions>()->GetContext().Has<Extension::IDynamicRendering>())
		{
			return CreateUP<RenderPass2>(context);
		}
		else
		{
			return CreateUP<RenderPass>(context);
		}
	}
}

#endif