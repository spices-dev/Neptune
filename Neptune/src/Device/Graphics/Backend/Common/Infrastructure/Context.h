/**
* @file Context.h.
* @brief The Context Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Device/Graphics/Backend/Common/Concept.h"
#include "Device/Graphics/Backend/Common/Context/Context.h"
#include "Core/Container/KVTuple.h"

#include <array>

namespace Neptune::Graphic::Common {

    template<typename E>
    requires IsEnum<E>
    class Infrastructure;
}

namespace Neptune::Graphic::Common {

    /**
    * @brief Template of Infrastructure Class Definitions.
    * 
    * @tparam T_ Infrastructure Class.
    * @tparam E_ EInfrastructure.
    */
    template<typename T_, auto E_>
    requires IsEnum<decltype(E_)>
	using IInfrastructure = IContextElement<T_, E_>;
    
    /**
    * @brief RenderBackend Context.
    * 
    * @tparam E EInfrastructure.
    */
    template<typename E>
    requires IsEnum<E>
    using IContext = Graphic::Common::Context<Infrastructure<E>, E>;

}