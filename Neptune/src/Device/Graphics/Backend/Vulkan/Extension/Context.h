/**
* @file Context.h.
* @brief The Context Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Extension.h"
#include "Concept.h"
#include "Enum.h"

namespace Neptune::Vulkan::Extension {
    
    /**
    * @brief Template of Extension Class Definitions.
    * 
    * @tparam T_ Extension Class.
    * @tparam E_ EExtension.
    */
    template<typename T_, auto E_>
    requires IsEnum<decltype(E_)>
    using IExtension = Graphic::Common::IContextElement<T_, E_>;
    
    /**
    * @brief Extension Context.
    * 
    * @tparam E EExtension.
    */
    template<typename E>
    requires IsEnum<E>
    using EContext = Graphic::Common::Context<Extension, E>;

}

#endif