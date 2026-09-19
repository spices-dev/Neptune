/**
* @file IImageLayout.cpp.
* @brief The IImageLayout Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IImageLayout.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/UnifiedImageLayouts.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DynamicRendering.h"

namespace Neptune::Vulkan::Middleware {
	
    UP<IImageLayout> IImageLayout::Create(Context& context)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (context.Get<IExtensions>()->GetContext()->Has<Extension::IUnifiedImageLayouts>())
        {
            return CreateUP<ImageLayout2>();
        }

        return CreateUP<ImageLayout>(context.Get<IExtensions>()->GetContext()->Has<Extension::IDynamicRendering>());
    }

    VkImageLayout ImageLayout::From(VkImageLayout layout) const
    {
        NEPTUNE_PROFILE_ZONE
        
        if (m_DynamicRendering && layout == VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL) return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        
        return layout;
    }

    VkImageLayout ImageLayout2::From(VkImageLayout layout) const
    {
        NEPTUNE_PROFILE_ZONE
        
        switch (layout)
        {
            case VK_IMAGE_LAYOUT_UNDEFINED:       return VK_IMAGE_LAYOUT_UNDEFINED;
            case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR: return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            default:                              return VK_IMAGE_LAYOUT_GENERAL;
        }
    }
}

#endif