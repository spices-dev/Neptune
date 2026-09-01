/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Surface.h"
#include "Window/Window.h"

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
            case WindowImplement::GLFW: return CreateUP<GLFW::Surface>(context, e, window);
#endif
            
#ifdef NP_WINDOW_ANDROIDNATIVE
            case WindowImplement::AndroidNative: return CreateUP<Android::Surface>(context, e, window);
#endif
            
            default:
            {
                NEPTUNE_LOG_CORE(E) << "Surface Create with WindowImplement that not supported.";
                return nullptr;
            }
        }
    }

}

#endif