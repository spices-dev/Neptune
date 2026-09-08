/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Concept.h"
#include "Device/Graphics/Backend/Common/Context/Context.h"
#include "Capability.h"

namespace Neptune::OpenGL::Capability {
    
    /**
    * @brief Concept: Is Capability.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsCapability = Graphic::Common::IsContextElement<Capability, T>;
    
    /**
    * @brief Concept: Is ICapability.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsICapability = Graphic::Common::IsIContextElement<Capability, T>;
    
    /**
    * @brief Concept: Is IsCoreCapability.
    * 
    * @tparam T IsCapability.
    */
    template<typename T>
    static constexpr bool IsCoreCapability = requires(T t) {
        t.CoreVersion;
        requires IsCapability<RemoveRef<T>>;
        requires OPENGL_VERSION >= t.CoreVersion;
    };
    
}

#endif