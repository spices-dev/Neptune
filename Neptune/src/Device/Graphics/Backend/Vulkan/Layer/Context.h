/**
* @file Context.h.
* @brief The Context Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Layer.h"
#include "Concept.h"
#include "Enum.h"

namespace Neptune::Vulkan::Layer {
    
    /**
    * @brief Template of Layer Class Definitions.
    * 
    * @tparam T_ Layer Class.
    * @tparam E_ ELayer.
    */
    template<typename T_, auto E_>
    requires IsEnum<decltype(E_)>
    using ILayer = Graphic::Common::IContextElement<T_, E_>;
    
    /**
    * @brief Layer Context.
    * 
    * @tparam E ELayer.
    */
    template<typename E>
    requires IsEnum<E>
    using LContext = Graphic::Common::Context<Layer, E>;

}

#endif