/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Device/Graphics/Backend/Common/Context/DirectedAcyclicGraph.h"

namespace Neptune::WebGPU {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        Extensions = 0,                      // @brief Extensions.
        Instance,                            // @brief Instance.
        DebugUtilsObject,                    // @brief Label/Name Functors.
        Adapter,                             // @brief Adapter.
        Device,                              // @brief LogicalDevice.
        Surface,                             // @brief Surface.

        Queue,                               // @brief Queue.
        
        GraphicTimeLine,                     // @brief GraphicTimeLine.
        ComputeTimeLine,                     // @brief ComputeTimeLine.

        GraphicCommandEncoder,               // @brief GraphicCommandEncoder.
        ComputeCommandEncoder,               // @brief ComputeCommandEncoder.
        
        GarbageCollection,                   // @brief GarbageCollection.
        AccessibleInfrastructures,           // @brief AccessibleInfrastructures.
        
        Count
    };

}

namespace Neptune::Graphic::Common {
    
    /**
    * @brief EInfrastructure Infrastructure DAG.
    */
    template<>
    inline constexpr DirectedAcyclicGraph<EInfrastructure> s_InfrastructureDAG<EInfrastructure>{{
        { WebGPU::EInfrastructure::Instance,                      { WebGPU::EInfrastructure::Extensions } },
        { WebGPU::EInfrastructure::DebugUtilsObject,              { WebGPU::EInfrastructure::Instance } },
        { WebGPU::EInfrastructure::Adapter,                       { WebGPU::EInfrastructure::Instance } },
        { WebGPU::EInfrastructure::Device,                        { WebGPU::EInfrastructure::Adapter } },
        { WebGPU::EInfrastructure::Surface,                       { WebGPU::EInfrastructure::Device } },
        { WebGPU::EInfrastructure::Queue,                         { WebGPU::EInfrastructure::Device } },
        { WebGPU::EInfrastructure::GraphicTimeLine,               { WebGPU::EInfrastructure::Device } },
        { WebGPU::EInfrastructure::ComputeTimeLine,               { WebGPU::EInfrastructure::Device } },
        { WebGPU::EInfrastructure::GraphicCommandEncoder,         { WebGPU::EInfrastructure::Device } },
        { WebGPU::EInfrastructure::ComputeCommandEncoder,         { WebGPU::EInfrastructure::Device } },
        { WebGPU::EInfrastructure::AccessibleInfrastructures,     { WebGPU::EInfrastructure::Device } },

    }};
}

#endif