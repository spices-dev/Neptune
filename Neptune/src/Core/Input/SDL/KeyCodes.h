/**
* @file KeyCodes.h.
* @brief The KeyCodes Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Input/KeyCodes.h"

#include <SDL3/SDL_keycode.h>

namespace Neptune::SDL {

    using namespace Neptune::Key;
    
    namespace Key {
        
        /**
        * @brief Convert SDL_Keycode to KeyCode.
        * 
        * @param key SDL_Keycode.
        * 
        * @return Returns KeyCode.
        */
        inline KeyCode ToKeyCode(SDL_Keycode key)
        {
            if (key >= SDLK_A && key <= SDLK_Z)
            {
                return static_cast<KeyCode>(A + (key - SDLK_A));
            }
            
            if (key >= SDLK_0 && key <= SDLK_9)
            {
                return static_cast<KeyCode>(D0 + (key - SDLK_0));
            }
            
            if (key >= SDLK_F1   && key <= SDLK_F12)  return static_cast<KeyCode>(F1  + (key - SDLK_F1));
            if (key >= SDLK_F13  && key <= SDLK_F24)  return static_cast<KeyCode>(F13 + (key - SDLK_F13));
            if (key >= SDLK_KP_1 && key <= SDLK_KP_9) return static_cast<KeyCode>(KP1 + (key - SDLK_KP_1));

            switch (key)
            {
                case SDLK_SPACE:        return Space;
                case SDLK_APOSTROPHE:   return Apostrophe;
                case SDLK_COMMA:        return Comma;
                case SDLK_MINUS:        return Minus;
                case SDLK_PERIOD:       return Period;
                case SDLK_SLASH:        return Slash;
                case SDLK_SEMICOLON:    return Semicolon;
                case SDLK_EQUALS:       return Equal;
                case SDLK_LEFTBRACKET:  return LeftBracket;
                case SDLK_BACKSLASH:    return Backslash;
                case SDLK_RIGHTBRACKET: return RightBracket;
                case SDLK_GRAVE:        return GraveAccent;

                case SDLK_ESCAPE:       return Escape;
                case SDLK_RETURN:       return Enter;
                case SDLK_TAB:          return Tab;
                case SDLK_BACKSPACE:    return Backspace;
                case SDLK_INSERT:       return Insert;
                case SDLK_DELETE:       return Delete;
                case SDLK_RIGHT:        return Right;
                case SDLK_LEFT:         return Left;
                case SDLK_DOWN:         return Down;
                case SDLK_UP:           return Up;
                case SDLK_PAGEUP:       return PageUp;
                case SDLK_PAGEDOWN:     return PageDown;
                case SDLK_HOME:         return Home;
                case SDLK_END:          return End;
                case SDLK_CAPSLOCK:     return CapsLock;
                case SDLK_SCROLLLOCK:   return ScrollLock;
                case SDLK_NUMLOCKCLEAR: return NumLock;
                case SDLK_PRINTSCREEN:  return PrintScreen;
                case SDLK_PAUSE:        return Pause;

                case SDLK_KP_0:         return KP0;
                case SDLK_KP_PERIOD:    return KPDecimal;
                case SDLK_KP_DIVIDE:    return KPDivide;
                case SDLK_KP_MULTIPLY:  return KPMultiply;
                case SDLK_KP_MINUS:     return KPSubtract;
                case SDLK_KP_PLUS:      return KPAdd;
                case SDLK_KP_ENTER:     return KPEnter;
                case SDLK_KP_EQUALS:    return KPEqual;

                case SDLK_LSHIFT:       return LeftShift;
                case SDLK_LCTRL:        return LeftControl;
                case SDLK_LALT:         return LeftAlt;
                case SDLK_LGUI:         return LeftSuper;
                case SDLK_RSHIFT:       return RightShift;
                case SDLK_RCTRL:        return RightControl;
                case SDLK_RALT:         return RightAlt;
                case SDLK_RGUI:         return RightSuper;
                case SDLK_APPLICATION:  return Menu;

                default:                return 0;
            }
        }
        
        /**
        * @brief Convert KeyCode to SDL_Keycode.
        * 
        * @param key KeyCode.
        * 
        * @return Returns SDL_Keycode.
        */
        inline SDL_Keycode ToSDLKeycode(KeyCode key)
        {
            if (key >= A && key <= Z)
            {
                return static_cast<SDL_Keycode>(SDLK_A + (key - A));
            }
            
            if (key >= D0 && key <= D9)
            {
                return static_cast<SDL_Keycode>(key);
            }
            
            if (key >= F1  && key <= F12) return static_cast<SDL_Keycode>(SDLK_F1   + (key - F1));
            if (key >= F13 && key <= F24) return static_cast<SDL_Keycode>(SDLK_F13  + (key - F13));
            if (key >= KP1 && key <= KP9) return static_cast<SDL_Keycode>(SDLK_KP_1 + (key - KP1));

            switch (key)
            {
                case Space:        return SDLK_SPACE;
                case Apostrophe:   return SDLK_APOSTROPHE;
                case Comma:        return SDLK_COMMA;
                case Minus:        return SDLK_MINUS;
                case Period:       return SDLK_PERIOD;
                case Slash:        return SDLK_SLASH;
                case Semicolon:    return SDLK_SEMICOLON;
                case Equal:        return SDLK_EQUALS;
                case LeftBracket:  return SDLK_LEFTBRACKET;
                case Backslash:    return SDLK_BACKSLASH;
                case RightBracket: return SDLK_RIGHTBRACKET;
                case GraveAccent:  return SDLK_GRAVE;

                case Escape:       return SDLK_ESCAPE;
                case Enter:        return SDLK_RETURN;
                case Tab:          return SDLK_TAB;
                case Backspace:    return SDLK_BACKSPACE;
                case Insert:       return SDLK_INSERT;
                case Delete:       return SDLK_DELETE;
                case Right:        return SDLK_RIGHT;
                case Left:         return SDLK_LEFT;
                case Down:         return SDLK_DOWN;
                case Up:           return SDLK_UP;
                case PageUp:       return SDLK_PAGEUP;
                case PageDown:     return SDLK_PAGEDOWN;
                case Home:         return SDLK_HOME;
                case End:          return SDLK_END;
                case CapsLock:     return SDLK_CAPSLOCK;
                case ScrollLock:   return SDLK_SCROLLLOCK;
                case NumLock:      return SDLK_NUMLOCKCLEAR;
                case PrintScreen:  return SDLK_PRINTSCREEN;
                case Pause:        return SDLK_PAUSE;

                case KP0:          return SDLK_KP_0;
                case KPDecimal:    return SDLK_KP_PERIOD;
                case KPDivide:     return SDLK_KP_DIVIDE;
                case KPMultiply:   return SDLK_KP_MULTIPLY;
                case KPSubtract:   return SDLK_KP_MINUS;
                case KPAdd:        return SDLK_KP_PLUS;
                case KPEnter:      return SDLK_KP_ENTER;
                case KPEqual:      return SDLK_KP_EQUALS;

                case LeftShift:    return SDLK_LSHIFT;
                case LeftControl:  return SDLK_LCTRL;
                case LeftAlt:      return SDLK_LALT;
                case LeftSuper:    return SDLK_LGUI;
                case RightShift:   return SDLK_RSHIFT;
                case RightControl: return SDLK_RCTRL;
                case RightAlt:     return SDLK_RALT;
                case RightSuper:   return SDLK_RGUI;
                case Menu:         return SDLK_APPLICATION;

                default:           return SDLK_UNKNOWN;
            }
        }
    }

}