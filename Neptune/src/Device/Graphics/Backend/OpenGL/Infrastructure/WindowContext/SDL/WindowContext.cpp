/**
* @file WindowContext.cpp.
* @brief The WindowContext Class Implementation.
* @author Spices.
*/
#include "Pchheader.h"

#if defined(NP_GRAPHICS_OPENGL) && defined(NP_WINDOW_SDL)

#include "WindowContext.h"
#include "Device/Graphics/Backend/OpenGL/Core.h"

#include <SDL3/SDL.h>

namespace Neptune::OpenGL::SDL {

    WindowContext::WindowContext(Context& context, EInfrastructure e, void* window)
        : OpenGL::WindowContext(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(window);
    }

    WindowContext::~WindowContext()
    {
        NEPTUNE_PROFILE_ZONE
        
        if (m_Window && m_OffScreen)
        {
            if (!SDL_GL_DestroyContext(SDL_GL_GetCurrentContext()))
            {
                NEPTUNE_LOG_CORE(C) << "SDL APIUnLoad Failed: " << SDL_GetError();
            }
            
            SDL_DestroyWindow(static_cast<SDL_Window*>(m_Window));
        }
    }

    void WindowContext::Create(void* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Window = window ? window : CreateWindow();

        MakeContextCurrent();

        // Turn off v-sync.
        SDL_GL_SetSwapInterval(0);

        // Use glad to load OpenGL APIs.
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            NEPTUNE_LOG_CORE(C) << "Failed to initialize GLAD";
        }
    }

    void* WindowContext::CreateWindow()
    {
        NEPTUNE_PROFILE_ZONE
        
        // Initialize the library
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            NEPTUNE_LOG_CORE(C) << "SDL Init Failed：" << SDL_GetError();
        }

        // Set OpenGL Version 4.6.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

#ifdef NEPTUNE_DEBUG

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

#endif

        auto window = SDL_CreateWindow("OpenGLContext", 1, 1, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);

        if (!window)
        {
            NEPTUNE_LOG_CORE(C) << "Window Create Failed: " << SDL_GetError();
            SDL_Quit();
        }

        m_OffScreen = true;
        
        return window;
    }
    
    void WindowContext::MakeContextCurrent()
    {
        NEPTUNE_PROFILE_ZONE

        auto ctx = m_OffScreen ? SDL_GL_CreateContext(static_cast<SDL_Window*>(m_Window)) : SDL_GL_GetCurrentContext();
        
        if (!SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_Window), ctx))
        {
            NEPTUNE_LOG_CORE(C) << "SDL APILoad Failed: " << SDL_GetError();
        }
    }
    
    void WindowContext::SwapBuffers()
    {
        NEPTUNE_PROFILE_ZONE
        
        SDL_GL_SwapWindow(static_cast<SDL_Window*>(m_Window));
    }
    
}

#endif