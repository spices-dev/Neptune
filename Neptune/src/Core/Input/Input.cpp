/**
* @file Input.h.
* @brief The Input Class Implementation.
* @author The Cherno.
*/

#include "Pchheader.h"
#include "Input.h"

#if defined(NP_WINDOW_GLFW) || defined(NP_WINDOW_EMSCRIPTENGLFW)
#include "GLFW/InputImpl.h"
#endif

#ifdef NP_WINDOW_SDL
#include "SDL/InputImpl.h"
#endif

#include "None/InputImpl.h"

namespace Neptune {

    namespace {
        
        UP<Input> s_Instance = nullptr;
    }
    
    void Input::Create(WindowImplement implement)
    {
        switch (implement)
        {
#if defined(NP_WINDOW_GLFW) || defined(NP_WINDOW_EMSCRIPTENGLFW)
            case WindowImplement::GLFW:
            case WindowImplement::emscripten_glfw:
            {
                s_Instance = CreateUP<GLFW::InputImpl>();
                break;
            }
#endif
            
#ifdef NP_WINDOW_SDL
            case WindowImplement::SDL:
            {
                s_Instance = CreateUP<SDL::InputImpl>();
                break;
            }
#endif
            
            default:
            {
                s_Instance = CreateUP<InputNone::InputImpl>();
                break;
            }
        }
    }

    bool Input::IsKeyPressed(const int& keycode)
    {
        return s_Instance->IsKeyPressedImpl(keycode);
    }

    bool Input::IsMouseButtonPressed(const int& button)
    {
        return s_Instance->IsMouseButtonPressedImpl(button);
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        return s_Instance->GetMousePositionImpl();
    }

    float Input::GetMouseX()
    {
        return s_Instance->GetMouseXImpl();
    }

    float Input::GetMouseY()
    {
        return s_Instance->GetMouseYImpl();
    }
}
