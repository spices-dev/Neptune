/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGLES

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGLES/Core.h"
#include "Device/Graphics/Backend/Common/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::OpenGLES {

    /**
    * @brief Enum of Accessible Infrastructure.
    */
    enum class EAccessibleInfrastructure : uint8_t
    {
        Count
    };
    
    using AInfrastructures = std::tuple<
    >;
    
    using AContext                = Graphic::Common::AccessibleContext<EAccessibleInfrastructure, AInfrastructures>;
    
}

#endif