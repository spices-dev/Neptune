/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Surface.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Display.h"
#include "Window/Window.h"
#include "Surface/Display/Surface.h"
#include "Surface/Headless/Surface.h"

#ifdef NP_WINDOW_GLFW
#include "Surface/GLFW/Surface.h"
#endif

#ifdef NP_WINDOW_ANDROIDNATIVE
#include "Surface/AndroidNative/Surface.h"
#endif

namespace Neptune::Vulkan {

    UP<Surface> Surface::Create(Context& context, EInfrastructure e, WindowImplement implement, void* window)
    {
        NEPTUNE_PROFILE_ZONE

        switch (implement)
        {
            
#ifdef NP_WINDOW_GLFW
            case WindowImplement::GLFW: return CreateUP<GLFW::Surface>(context, e, implement, window);
#endif
            
#ifdef NP_WINDOW_ANDROIDNATIVE
            case WindowImplement::AndroidNative: return CreateUP<AndroidNative::Surface>(context, e, implement, window);
#endif
            
            case WindowImplement::Simulate: return CreateUP<Display::Surface>(context, e, implement);
            case WindowImplement::Headless: return CreateUP<Headless::Surface>(context, e, implement);
            default:
            {
                NEPTUNE_LOG_CORE(E) << "Surface Create with WindowImplement that not supported.";
                return nullptr;
            }
        }
    }

}

#endif