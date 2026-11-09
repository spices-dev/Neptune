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
        Device = 0,                      // @brief Device
        RenderPassDescriptor,            // @brief RenderPassDescriptor
        
        Count
    };
    
    using ADevice                = Graphic::Common::AccessibleInfrastructure<MTL::Device*,               EAccessibleInfrastructure::Device>;
    using ARenderPassDescriptor  = Graphic::Common::AccessibleInfrastructure<MTL::RenderPassDescriptor*, EAccessibleInfrastructure::RenderPassDescriptor>;
    
    using AInfrastructures = std::tuple<
        ADevice::T, 
        ARenderPassDescriptor::T
    >;
    
    struct AContext : Graphic::Common::AccessibleContext<EAccessibleInfrastructure, AInfrastructures> {};
    
}

#endif