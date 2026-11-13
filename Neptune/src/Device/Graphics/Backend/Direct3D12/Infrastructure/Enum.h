/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Device/Graphics/Backend/Common/Context/DirectedAcyclicGraph.h"

namespace Neptune::Direct3D12 {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        Extensions,                          // @brief Extensions.
        DebugUtilsObject,                    // @brief Label/Name Functors.
        Factory,                             // @brief DXGI Factory.
        Device,                              // @brief LogicalDevice.

        GraphicQueue,                        // @brief Main Thread Graphic Queue.
        ComputeQueue,                        // @brief Main Thread Compute Queue.

        SwapChain,                           // @brief SwapChain.

        GraphicTimeLine,                     // @brief Main Thread Graphic TimeLine.
        ComputeTimeLine,                     // @brief Main Thread Compute TimeLine.

        GraphicCommandList,                  // @brief Main Thread Graphic CommandList.
        ComputeCommandList,                  // @brief Main Thread Compute CommandList.

        RTVDescriptorHeap,                   // @brief Render Target View DescriptorHeap.
        DSVDescriptorHeap,                   // @brief Depth Stencil View DescriptorHeap.
        SRVDescriptorHeap,                   // @brief Shader Resource View DescriptorHeap.
        UAVDescriptorHeap,                   // @brief Unordered Access View DescriptorHeap.
        
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
    inline constexpr DirectedAcyclicGraph<Direct3D12::EInfrastructure> s_InfrastructureDAG<Direct3D12::EInfrastructure>{{
        { Direct3D12::EInfrastructure::Device,                        { Direct3D12::EInfrastructure::Factory } },
        { Direct3D12::EInfrastructure::GraphicQueue,                  { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::ComputeQueue,                  { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::SwapChain,                     { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::GraphicTimeLine,               { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::ComputeTimeLine,               { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::GraphicCommandList,            { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::ComputeCommandList,            { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::RTVDescriptorHeap,             { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::DSVDescriptorHeap,             { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::SRVDescriptorHeap,             { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::UAVDescriptorHeap,             { Direct3D12::EInfrastructure::Device } },
        { Direct3D12::EInfrastructure::AccessibleInfrastructures,     { Direct3D12::EInfrastructure::Device } },
    }};
}

#endif