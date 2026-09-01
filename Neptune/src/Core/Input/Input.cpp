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

namespace Neptune {

    /**
    * @brief Instance a WindowsInput single instance.
    */
#if defined(NP_WINDOW_GLFW) || defined(NP_WINDOW_EMSCRIPTENGLFW)
    
    std::unique_ptr<Input> Input::s_Instance = std::make_unique<GLFW::InputImpl>();
    
#endif

}