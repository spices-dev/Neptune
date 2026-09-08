/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D11/Core.h"
#include "Device/Graphics/Backend/Common/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::Direct3D11 {

    /**
    * @brief Enum of Accessible Infrastructure.
    */
    enum class EAccessibleInfrastructure : uint8_t
    {
        Device = 0,             // @brief Device
        DeviceContext,          // @brief DeviceContext

        Count
    };

    using ADevice               = Graphic::Common::AccessibleInfrastructure<ID3D11Device*,          EAccessibleInfrastructure::Device>;
    using ADeviceContext        = Graphic::Common::AccessibleInfrastructure<ID3D11DeviceContext*,   EAccessibleInfrastructure::DeviceContext>;

    using AContext              = Graphic::Common::AccessibleContext<EAccessibleInfrastructure>;
    
}

#endif