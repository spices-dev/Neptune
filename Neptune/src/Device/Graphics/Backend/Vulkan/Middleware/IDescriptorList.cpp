/**
* @file IDescriptorList.cpp.
* @brief The IDescriptorList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IDescriptorList.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DescriptorHeap.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DescriptorBuffer.h"

namespace Neptune::Vulkan::Middleware {
	
    UP<IDescriptorList> IDescriptorList::Create(Context& context)
    {
        NEPTUNE_PROFILE_ZONE
		
        if (context.Get<IExtensions>()->GetContext()->Has<Extension::IDescriptorHeap>())
        {
            return nullptr;
        }
        if (context.Get<IExtensions>()->GetContext()->Has<Extension::IDescriptorBuffer>())
        {
            return nullptr;
        }
		
        return nullptr;
    }
}

#endif