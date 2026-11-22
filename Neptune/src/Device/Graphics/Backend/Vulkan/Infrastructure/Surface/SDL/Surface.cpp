/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#if defined(NP_GRAPHICS_VULKAN) && defined(NP_WINDOW_SDL)

#include "Surface.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Instance.h"

#include <SDL3/SDL_vulkan.h>

namespace Neptune::Vulkan::SDL {

    Surface::Surface(Context& context, EInfrastructure e, WindowImplement implement, void* window)
        : Vulkan::Surface(context, e, implement)
    {
        NEPTUNE_PROFILE_ZONE

        Create(window);
    }

    void Surface::Create(void* window)
    {
        NEPTUNE_PROFILE_ZONE

        const auto instance = GetContext().Get<IInstance>()->Handle();

        Unit::Surface::Handle handle;

        if (!SDL_Vulkan_CreateSurface(static_cast<SDL_Window*>(window), instance, GetAllocator(), &handle))
        {
            NEPTUNE_LOG_CORE(C) << "SDL Surface Create Failed: " << SDL_GetError();
        }
        
        m_Surface.SetHandle(handle);

        m_Surface.SetInstance(instance);
    }

}

#endif