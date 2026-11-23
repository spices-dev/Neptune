/**
* @file InputImpl.h.
* @brief The InputImpl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_WINDOW_SDL

#include "InputImpl.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

#include <SDL3/SDL.h>

namespace Neptune::SDL {

    bool InputImpl::IsKeyPressedImpl(const int& keycode)
    {
        const bool* state = SDL_GetKeyboardState(nullptr);

        auto sdlKey = Key::ToSDLKeycode(static_cast<KeyCode>(keycode));
        if (sdlKey == SDLK_UNKNOWN)
        {
            return false;
        }
        
        auto sc = SDL_GetScancodeFromKey(sdlKey, nullptr); 
        if (sc == SDL_SCANCODE_UNKNOWN)
        {
            return false;
        }
        
        return state[sc];
    }

    bool InputImpl::IsMouseButtonPressedImpl(const int& button)
    {
        const auto flags = SDL_GetMouseState(nullptr, nullptr);

        return (flags & SDL_BUTTON_MASK(Mouse::ToSDLButton(static_cast<MouseCode>(button)))) != 0;
    }

    std::pair<float, float> InputImpl::GetMousePositionImpl()
    {
        float xPos = 0.0f;
        float yPos = 0.0f;

        SDL_GetMouseState(&xPos, &yPos);

        return { xPos, yPos };
    }

    float InputImpl::GetMouseXImpl()
    {
        auto [x, y] = GetMousePositionImpl();

        return x;
    }

    float InputImpl::GetMouseYImpl()
    {
        auto [x, y] = GetMousePositionImpl();

        return y;
    }
}

#endif