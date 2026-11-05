/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGL/Core.h"
#include "Device/Graphics/Backend/Common/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::WebGL {

    /**
    * @brief Enum of Accessible Infrastructure.
    */
    enum class EAccessibleInfrastructure : uint8_t
    {
        Count
    };
    
    using AInfrastructures = std::tuple<
    >;
    
    using AContext = Graphic::Common::AccessibleContext<EAccessibleInfrastructure, AInfrastructures>;
    
}

#endif