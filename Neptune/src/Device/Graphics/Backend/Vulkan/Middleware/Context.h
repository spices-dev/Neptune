/**
* @file Context.h.
* @brief The Context Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Middleware.h"
#include "Enum.h"
#include "Device/Graphics/Backend/Common/Context/Context.h"

namespace Neptune::Vulkan::Middleware {
    
    /**
    * @brief Template of Middleware Class Definitions.
    * 
    * @tparam T_ Middleware Class.
    * @tparam E_ EMiddleware.
    */
    template<typename T_, auto E_>
    requires IsEnum<decltype(E_)>
    using IMiddleware = Graphic::Common::IContextElement<T_, E_>;
    
    /**
    * @brief Middleware Context.
    * 
    * @tparam E EMiddleware.
    */
    template<typename E>
    requires IsEnum<E>
    using MContext = Graphic::Common::Context<Middleware, E>;

}

#endif