/**
* @file WindowContext.cpp.
* @brief The WindowContext Class Implementation.
* @author Spices.
*/
#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "WindowContext.h"

#ifdef NP_WINDOW_GLFW
#include "WindowContext/GLFW/WindowContext.h"
#endif

namespace Neptune::OpenGL {

    UP<WindowContext> WindowContext::Create(Context& context, EInfrastructure e, WindowImplement implement, void* window)
	{
        NEPTUNE_PROFILE_ZONE

        switch (implement)
        {
#ifdef NP_WINDOW_GLFW
            case WindowImplement::GLFW: return CreateUP<GLFW::WindowContext>(context, e, window);
#endif
            default:
            {
                NEPTUNE_LOG_CORE(E) << "WindowContext Create with WindowImplement that not supported.";
                return nullptr;
            }
        }
	}
}

#endif