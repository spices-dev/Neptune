/**
* @file Context.h.
* @brief The Context Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Capability.h"
#include "Concept.h"
#include "Enum.h"

namespace Neptune::OpenGL::Capability {
    
    /**
    * @brief Template of Capability Class Definitions.
    * 
    * @tparam T_ Capability Class.
    * @tparam E_ ECapability.
    */
    template<typename T_, auto E_>
    requires IsEnum<decltype(E_)>
    using ICapability = Graphic::Common::IContextElement<T_, E_>;
    
    /**
    * @brief Capability Context.
    * 
    * @tparam E ECapability.
    */
    template<typename E>
    requires IsEnum<E>
    using CContext = Graphic::Common::Context<Capability, E>;

}

#endif