/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Device/Graphics/Backend/Common/Context/DirectedAcyclicGraph.h"

namespace Neptune::Vulkan {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        Functions = 0,                       // @brief Functors.
        Layers,                              // @brief Layers.
        Extensions,                          // @brief Extensions.
        Instance,                            // @brief Instance.
        DebugUtilsObject,                    // @brief Label/Name Functors.
        Surface,                             // @brief Surface.
        PhysicalDevice,                      // @brief PhysicalDevice.
        Device,                              // @brief LogicalDevice.
                                             
        GraphicQueue,                        // @brief Main Thread Graphic Queue.
        PresentQueue,                        // @brief Main Thread Present Queue.
        ComputeQueue,                        // @brief Main Thread Compute Queue.

        GraphicThreadQueue,                  // @brief Sub Thread Graphic Queue.
        ComputeThreadQueue,                  // @brief Sub Thread Compute Queue.
        TransferThreadQueue,                 // @brief Sub Thread Transfer Queue.
        VideoEncodeThreadQueue,              // @brief Sub Thread VideoEncode Queue.
        VideoDecodeThreadQueue,              // @brief Sub Thread VideoDecode Queue.
        OpticalFlowThreadQueue,              // @brief Sub Thread OpticalFlow Queue.
                                             
        MemoryAllocator,                     // @brief VMA.
        SwapChain,                           // @brief SwapChain.

        GraphicTimeLine,                     // @brief GraphicTimeLine.
        ComputeTimeLine,                     // @brief ComputeTimeLine.
        
        GraphicImageSemaphore,               // @brief Main Thread Graphic ImageSemaphore.
        GraphicQueueSemaphore,               // @brief Main Thread Graphic QueueSemaphore.
                                             
        GraphicCommandPool,                  // @brief Main Thread Graphic CommandPool.
        GraphicCommandBuffer,                // @brief Main Thread Graphic CommandBuffer.

        ComputeCommandPool,                  // @brief Main Thread Compute CommandPool.
        ComputeCommandBuffer,                // @brief Main Thread Compute CommandBuffer.

        GraphicThreadCommandPool,            // @brief Sub Thread Graphic CommandPool.
        ComputeThreadCommandPool,            // @brief Sub Thread Compute CommandPool.
        TransferThreadCommandPool,           // @brief Sub Thread Transfer CommandPool.
        VideoEncodeThreadCommandPool,        // @brief Sub Thread VideoEncode CommandPool.
        VideoDecodeThreadCommandPool,        // @brief Sub Thread VideoDecode CommandPool.
        OpticalFlowThreadCommandPool,        // @brief Sub Thread OpticalFlow CommandPool.

        DescriptorPool,                      // @brief DescriptorPool.
        
        Middlewares,                         // @brief Middlewares.
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
    inline constexpr DirectedAcyclicGraph<Vulkan::EInfrastructure> s_InfrastructureDAG<Vulkan::EInfrastructure>{{
        { Vulkan::EInfrastructure::Instance,                      { Vulkan::EInfrastructure::Functions, Vulkan::EInfrastructure::Layers, Vulkan::EInfrastructure::Extensions } },
        { Vulkan::EInfrastructure::DebugUtilsObject,              { Vulkan::EInfrastructure::Instance } },
        { Vulkan::EInfrastructure::Surface,                       { Vulkan::EInfrastructure::Instance } },
        { Vulkan::EInfrastructure::PhysicalDevice,                { Vulkan::EInfrastructure::Instance } },
        { Vulkan::EInfrastructure::Device,                        { Vulkan::EInfrastructure::PhysicalDevice } },
        { Vulkan::EInfrastructure::GraphicQueue,                  { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::PresentQueue,                  { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::ComputeQueue,                  { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::GraphicThreadQueue,            { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::ComputeThreadQueue,            { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::TransferThreadQueue,           { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::VideoEncodeThreadQueue,        { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::VideoDecodeThreadQueue,        { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::OpticalFlowThreadQueue,        { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::MemoryAllocator,               { Vulkan::EInfrastructure::Instance } },
        { Vulkan::EInfrastructure::SwapChain,                     { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::GraphicTimeLine,               { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::ComputeTimeLine,               { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::GraphicImageSemaphore,         { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::GraphicQueueSemaphore,         { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::GraphicCommandPool,            { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::GraphicCommandBuffer,          { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::ComputeCommandPool,            { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::ComputeCommandBuffer,          { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::GraphicThreadCommandPool,      { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::ComputeThreadCommandPool,      { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::TransferThreadCommandPool,     { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::VideoEncodeThreadCommandPool,  { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::OpticalFlowThreadCommandPool,  { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::DescriptorPool,                { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::Middlewares,                   { Vulkan::EInfrastructure::Device } },
        { Vulkan::EInfrastructure::AccessibleInfrastructures,     { Vulkan::EInfrastructure::PhysicalDevice } },
    }};
}

#endif