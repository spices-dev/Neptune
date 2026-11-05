/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

namespace Neptune::OpenGL {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        WindowContext = 0,                   // @brief Window/Context.
        Extensions,                          // @brief Extensions.
        DebugUtilsObject,                    // @brief Label/Name Functors.

        TimeLine,                            // @brief Main Thread TimeLine.
        
        AccessibleInfrastructures,           // @brief AccessibleInfrastructures.

        Count
    };

}

#endif