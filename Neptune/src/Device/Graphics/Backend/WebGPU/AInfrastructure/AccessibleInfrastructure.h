/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Core.h"
#include "Device/Graphics/Backend/Common/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::WebGPU {

    /**
    * @brief Enum of Accessible Infrastructure.
    */
    enum class EAccessibleInfrastructure : uint8_t
    {
        Device = 0,             // @brief Device
        RTVFormat,              // @brief RTVFormat
        DSVFormat,              // @brief DSVFormat

        Count
    };

    using ADevice           = Graphic::Common::AccessibleInfrastructure<WGPUDevice,          EAccessibleInfrastructure::Device>;
    using ARTVFormat        = Graphic::Common::AccessibleInfrastructure<WGPUTextureFormat,   EAccessibleInfrastructure::RTVFormat>;
    using ADSVFormat        = Graphic::Common::AccessibleInfrastructure<WGPUTextureFormat,   EAccessibleInfrastructure::DSVFormat>;

    using AInfrastructures = std::tuple<
        ADevice::T
        ARTVFormat::T
        ADSVFormat::T
    >;
    
    using AContext          = Graphic::Common::AccessibleContext<EAccessibleInfrastructure, AInfrastructures>;
    
}

#endif