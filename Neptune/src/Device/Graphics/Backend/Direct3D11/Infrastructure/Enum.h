/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Device/Graphics/Backend/Common/Context/DirectedAcyclicGraph.h"

namespace Neptune::Direct3D11 {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        DebugUtilsObject,                    // @brief Label/Name Functors.
        DeviceContext,                       // @brief Device Immediate Context.
        Factory,                             // @brief DXGI Factory.
        Device,                              // @brief LogicalDevice.
        
        SwapChain,                           // @brief SwapChain.

        GraphicFence,                        // @brief Main Thread Graphic Fence.
        ComputeFence,                        // @brief Main Thread Compute Fence.

        GraphicCommandList,                  // @brief Main Thread Graphic CommandList.
        ComputeCommandList,                  // @brief Main Thread Compute CommandList.

        GraphicThreadCommandList,            // @brief Sub Thread Graphic CommandList.
        ComputeThreadCommandList,            // @brief Sub Thread Compute CommandList.
        
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
    inline constexpr DirectedAcyclicGraph<Direct3D11::EInfrastructure> s_InfrastructureDAG<Direct3D11::EInfrastructure>{{
        { Direct3D11::EInfrastructure::Device,                        { Direct3D11::EInfrastructure::Factory } },
        { Direct3D11::EInfrastructure::SwapChain,                     { Direct3D11::EInfrastructure::Device } },
        { Direct3D11::EInfrastructure::GraphicFence,                  { Direct3D11::EInfrastructure::Device } },
        { Direct3D11::EInfrastructure::ComputeFence,                  { Direct3D11::EInfrastructure::Device } },
        { Direct3D11::EInfrastructure::GraphicCommandList,            { Direct3D11::EInfrastructure::Device } },
        { Direct3D11::EInfrastructure::ComputeCommandList,            { Direct3D11::EInfrastructure::Device } },
        { Direct3D11::EInfrastructure::GraphicThreadCommandList,      { Direct3D11::EInfrastructure::Device } },
        { Direct3D11::EInfrastructure::ComputeThreadCommandList,      { Direct3D11::EInfrastructure::Device } },
        { Direct3D11::EInfrastructure::AccessibleInfrastructures,     { Direct3D11::EInfrastructure::Device } },
    }};
}

#endif