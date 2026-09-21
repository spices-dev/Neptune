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

#include "None/InputImpl.h"

namespace Neptune {

    namespace {
        
        UP<Input> s_Instance = nullptr;
    }
    
    void Input::Create(WindowImplement implement)
    {
        NEPTUNE_PROFILE_ZONE
        
        switch (implement)
        {
            case WindowImplement::GLFW:
            case WindowImplement::emscripten_glfw:
#if defined(NP_WINDOW_GLFW) || defined(NP_WINDOW_EMSCRIPTENGLFW)
            {
                s_Instance = CreateUP<GLFW::InputImpl>();
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
        NEPTUNE_PROFILE_ZONE

        return s_Instance->IsKeyPressedImpl(keycode);
    }

    bool Input::IsMouseButtonPressed(const int& button)
    {
        NEPTUNE_PROFILE_ZONE
        
        return s_Instance->IsMouseButtonPressedImpl(button);
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        NEPTUNE_PROFILE_ZONE

        return s_Instance->GetMousePositionImpl();
    }

    float Input::GetMouseX()
    {
        NEPTUNE_PROFILE_ZONE
        
        return s_Instance->GetMouseXImpl();
    }

    float Input::GetMouseY()
    {
        NEPTUNE_PROFILE_ZONE
        
        return s_Instance->GetMouseYImpl();
    }
}
