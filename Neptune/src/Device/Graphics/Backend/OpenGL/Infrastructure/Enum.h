/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Device/Graphics/Backend/Common/Context/DirectedAcyclicGraph.h"

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
        
        GarbageCollection,                   // @brief GarbageCollection.
        AccessibleInfrastructures,           // @brief AccessibleInfrastructures.

        Count
    };

}

namespace Neptune::Graphic::Common {
    
    /**
    * @brief EInfrastructure Infrastructure DAG.
    */
    template<>
    inline constexpr DirectedAcyclicGraph<OpenGL::EInfrastructure> s_InfrastructureDAG<OpenGL::EInfrastructure>{{
        { OpenGL::EInfrastructure::Extensions,                    { OpenGL::EInfrastructure::WindowContext } },
        { OpenGL::EInfrastructure::DebugUtilsObject,              { OpenGL::EInfrastructure::Extensions } },
        { OpenGL::EInfrastructure::TimeLine,                      { OpenGL::EInfrastructure::WindowContext } },
        { OpenGL::EInfrastructure::AccessibleInfrastructures,     { OpenGL::EInfrastructure::WindowContext } },
    }};
}

#endif