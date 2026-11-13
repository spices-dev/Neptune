/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Device/Graphics/Backend/Common/Context/DirectedAcyclicGraph.h"

namespace Neptune::Metal {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        FrameAutoreleasePool,                // @brief FrameAutoreleasePool.
        Device,                              // @brief LogicalDevice.
        Layer,                               // @brief Layer.
        CommandQueue,                        // @brief CommandQueue.
        CommandBuffer,                       // @brief CommandBuffer.
        GraphicDispatchSemaphore,            // @brief GraphicDispatchSemaphore.
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
    inline constexpr DirectedAcyclicGraph<Metal::EInfrastructure> s_InfrastructureDAG<Metal::EInfrastructure>{{
        { Metal::EInfrastructure::Device,                        { Metal::EInfrastructure::FrameAutoreleasePool } },
        { Metal::EInfrastructure::Layer,                         { Metal::EInfrastructure::Device } },
        { Metal::EInfrastructure::CommandQueue,                  { Metal::EInfrastructure::Device } },
        { Metal::EInfrastructure::CommandBuffer,                 { Metal::EInfrastructure::Device } },
        { Metal::EInfrastructure::GraphicDispatchSemaphore,      { Metal::EInfrastructure::Device } },
        { Metal::EInfrastructure::AccessibleInfrastructures,     { Metal::EInfrastructure::Device } },
    }};
}

#endif