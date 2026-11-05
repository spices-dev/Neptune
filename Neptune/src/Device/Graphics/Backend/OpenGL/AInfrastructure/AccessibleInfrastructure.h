/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGL/Core.h"
#include "Device/Graphics/Backend/Common/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::OpenGL {

    /**
    * @brief Enum of Accessible Infrastructure.
    */
    enum class EAccessibleInfrastructure : uint8_t
    {
        ApiVersionName,             // @brief ApiVersionName.
        Count
    };
    
    using AApiVersionName         = Graphic::Common::AccessibleInfrastructure<const char*, EAccessibleInfrastructure::ApiVersionName>;
    
    using AInfrastructures = std::tuple<
        AApiVersionName::T
    >;
    
    using AContext                = Graphic::Common::AccessibleContext<EAccessibleInfrastructure, AInfrastructures>;
    
}

#endif