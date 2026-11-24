/**
* @file WindowImpl.cpp.
* @brief The WindowImpl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_WINDOW_SDL

#include "WindowImpl.h"
#include "RenderBackendInterface.h"
#include "Core/Event/WindowEvent.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"
#include "Core/Input/SDL/KeyCodes.h"
#include "Core/Input/SDL/MouseButtonCodes.h"

#include <SDL3/SDL.h>

namespace Neptune::SDL {

    namespace {
        
        /**
        * @brief Hit Test.
        * 
        * @param window SDL_Window.
        * @param area SDL_Point.
        * @param data Unused.
        * 
        * @return Returns SDL_HitTestResult.
        */
        SDL_HitTestResult HitTestCallback(SDL_Window* window, const SDL_Point* area, void* data)
        {
            constexpr int titleBarHeight = 32;
            constexpr int border         = 6;

            int w, h;
            SDL_GetWindowSize(window, &w, &h);

            const int x = area->x;
            const int y = area->y;
            
            const bool left   = x < border;
            const bool right  = x >= w - border;
            const bool top    = y < border;
            const bool bottom = y >= h - border;

            if (top && left)     return SDL_HITTEST_RESIZE_TOPLEFT;
            if (top && right)    return SDL_HITTEST_RESIZE_TOPRIGHT;
            if (bottom && left)  return SDL_HITTEST_RESIZE_BOTTOMLEFT;
            if (bottom && right) return SDL_HITTEST_RESIZE_BOTTOMRIGHT;
            if (top)             return SDL_HITTEST_RESIZE_TOP;
            if (bottom)          return SDL_HITTEST_RESIZE_BOTTOM;
            if (left)            return SDL_HITTEST_RESIZE_LEFT;
            if (right)           return SDL_HITTEST_RESIZE_RIGHT;
            
            if (y < titleBarHeight)
            {
                return SDL_HITTEST_DRAGGABLE;
            }

            return SDL_HITTEST_NORMAL;
        }
    }
    
    WindowImpl::WindowImpl(const WindowInfo& initInfo, WindowImplement implement, RenderBackendEnum backend, void* payload)
        : Window(implement)
        , EventProducer(EventType::Count)
        , m_APIInterface(CreateInterface(backend))
    {
        NEPTUNE_PROFILE_ZONE
        
        if(!SDL_Init(SDL_INIT_VIDEO)) 
        {
            NEPTUNE_LOG_CORE(C) << "SDL Init Failed: " << SDL_GetError();
        }
        
        NEPTUNE_LOG_CORE(I) << "SDL Info: " 
            << SDL_VERSIONNUM_MAJOR(SDL_GetVersion()) << "."
            << SDL_VERSIONNUM_MINOR(SDL_GetVersion()) << "."
            << SDL_VERSIONNUM_MICRO(SDL_GetVersion()) << " | "
            << SDL_GetCurrentVideoDriver();
        
        auto flag = m_APIInterface->Hint();
        
        m_Windows = SDL_CreateWindow(initInfo.name.c_str(), initInfo.width, initInfo.height, flag | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_BORDERLESS);
        if(!m_Windows) 
        {
            NEPTUNE_LOG_CORE(C) << "Window Create Failed: " << SDL_GetError();
            SDL_Quit();
        }
        
        SDL_SetWindowHitTest(m_Windows, HitTestCallback, nullptr);
        
        m_APIInterface->APILoad(m_Windows);
    }

    WindowImpl::~WindowImpl()
    {
        NEPTUNE_PROFILE_ZONE

        if (m_Windows) 
        {
            m_APIInterface->APIUnLoad();
            
            SDL_DestroyWindow(m_Windows);
        }

        SDL_Quit();
    }

    bool WindowImpl::PollEvents() const
    {
        NEPTUNE_PROFILE_ZONE

        SDL_Event e;
        
        while (SDL_PollEvent(&e)) 
        {
            ProcessEvent(e);
            
            if (e.type == SDL_EVENT_QUIT)
            {
                return false;
            }
        }
        
        return true;
    }

    glm::uvec2 WindowImpl::Extent() const
    {
        NEPTUNE_PROFILE_ZONE

        int width = 0, height = 0;
        SDL_GetWindowSizeInPixels(m_Windows, &width, &height);

        while (width == 0 || height == 0)
        {
            SDL_Event e;

            if (SDL_WaitEvent(&e))
            {
                if (e.type == SDL_EVENT_QUIT)
                {
                    SDL_PushEvent(&e);
                    
                    break;
                }
            }
        }

        return { width , height };
    }

    std::vector<const char*> WindowImpl::Extension() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return m_APIInterface->Extension();
    }
    
    void* WindowImpl::NativeWindow() const
    {
        NEPTUNE_PROFILE_ZONE

        return m_Windows;
    }

    void WindowImpl::ProcessEvent(const SDL_Event& e) const
    {
        NEPTUNE_PROFILE_ZONE
        
        m_EventDelegate.onSlateEvent.Broadcast(&e);
        
        switch (e.type)
        {
            // Window resize event Callback.
            case SDL_EVENT_WINDOW_RESIZED:
            {
                if (e.window.windowID != SDL_GetWindowID(m_Windows)) break;

                WindowResizeEvent event(e.window.data1, e.window.data2);
                
                Dispatch(event);
                
                break;
            }
            // Window close event Callback.
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                if (e.window.windowID != SDL_GetWindowID(m_Windows)) break;

                WindowCloseEvent event;
                
                Dispatch(event);
                
                break;
            }
            // Key event Callback.
            case SDL_EVENT_KEY_DOWN:
            {
                KeyPressedEvent event(Key::ToKeyCode(e.key.key), e.key.repeat ? 1 : 0);
                
                Dispatch(event);
                
                break;
            }
            case SDL_EVENT_KEY_UP:
            {
                KeyReleasedEvent event(Key::ToKeyCode(e.key.key));
                
                Dispatch(event);
                
                break;
            }
            // Key Input event Callback.
            case SDL_EVENT_TEXT_INPUT:
            {
                const char* p = e.text.text;
                
                while (*p)
                {
                    KeyTypedEvent event(Key::ToKeyCode(*p));
                    
                    Dispatch(event);
                    
                    ++p;
                }
                
                break;
            }
            // Mouse Button event Callback.
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {
                MouseButtonPressedEvent event(Mouse::ToSDLButton(e.button.button));
                
                Dispatch(event);
                
                break;
            }
            case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                MouseButtonReleasedEvent event(Mouse::ToSDLButton(e.button.button));
                
                Dispatch(event);
                
                break;
            }
            // Mouse Scroll event Callback.
            case SDL_EVENT_MOUSE_WHEEL:
            {
                MouseScrolledEvent event(e.wheel.x, e.wheel.y);
                
                Dispatch(event);
                
                break;
            }

            // Mouse Move event Callback.
            case SDL_EVENT_MOUSE_MOTION:
            {
                MouseMovedEvent event(e.motion.x, e.motion.y);
                
                Dispatch(event);
                
                break;
            }
            default: break;
        }
    }

}

#endif