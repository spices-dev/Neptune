/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Device/Graphics/Backend/Metal/Core.h"
#include "Device/Graphics/Backend/Common/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::Metal {

    /**
    * @brief Enum of Accessible Infrastructure.
    */
    enum class EAccessibleInfrastructure : uint8_t
    {
        Device = 0,             // @brief Device
        
        Count
    };
    
    using ADevice  = Graphic::Common::AccessibleInfrastructure<MTL::Device*, EAccessibleInfrastructure::Device>;
    
    using AContext = Graphic::Common::AccessibleContext<EAccessibleInfrastructure>;
    
}

#endif