/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

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

        Count
    };

}

#endif