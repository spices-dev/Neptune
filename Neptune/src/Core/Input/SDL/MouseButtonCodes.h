/**
* @file MouseButtonCodes.h.
* @brief The MouseButtonCodes Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Input/MouseButtonCodes.h"

#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_stdinc.h>

namespace Neptune::SDL {

    using namespace Neptune::Mouse;
    
    namespace Mouse {
        
        /**
        * @brief Convert SDLButton to MouseCode.
        * 
        * @param button SDLButton.
        * 
        * @return Returns MouseCode.
        */
        inline MouseCode ToMouseCode(Uint8 button)
        {
            switch (button)
            {
                case SDL_BUTTON_LEFT:   return ButtonLeft;    // 0
                case SDL_BUTTON_RIGHT:  return ButtonRight;   // 1
                case SDL_BUTTON_MIDDLE: return ButtonMiddle;  // 2
                case SDL_BUTTON_X1:     return Button3;
                case SDL_BUTTON_X2:     return Button4;
                default:                return ButtonLast + 1;
            }
        }
        
        /**
        * @brief Convert MouseCode to SDLButton.
        * 
        * @param button MouseCode.
        * 
        * @return Returns SDLButton.
        */
        inline Uint8 ToSDLButton(MouseCode button)
        {
            switch (button)
            {
                case ButtonLeft:   return SDL_BUTTON_LEFT;    // Button0
                case ButtonRight:  return SDL_BUTTON_RIGHT;   // Button1
                case ButtonMiddle: return SDL_BUTTON_MIDDLE;  // Button2
                case Button3:      return SDL_BUTTON_X1;
                case Button4:      return SDL_BUTTON_X2;
                default:           return 0;
            }
        }
    }

}
