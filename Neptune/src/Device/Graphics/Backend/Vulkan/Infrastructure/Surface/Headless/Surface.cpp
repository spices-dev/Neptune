/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Surface.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Instance.h"

namespace Neptune::Vulkan::Headless {

    Surface::Surface(Context& context, EInfrastructure e, WindowImplement implement)
        : Vulkan::Surface(context, e, implement)
    {
        NEPTUNE_PROFILE_ZONE
        
        Create();
    }

    void Surface::Create()
    {
        NEPTUNE_PROFILE_ZONE
        
        VkHeadlessSurfaceCreateInfoEXT       info{};
        info.sType                         = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
        
        m_Surface.CreateHeadlessSurface(GetContext().Get<IInstance>()->Handle(), info);
    }

}

#endif