/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Device/Graphics/Backend/Common/Infrastructure/DirectedAcyclicGraph.h"

#ifdef NP_GRAPHICS_VULKAN

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

    inline constexpr Graphic::Common::DirectedAcyclicGraph<EInfrastructure> g{{
        { EInfrastructure::Functions,{} },
        { EInfrastructure::Layers,{} },
        { EInfrastructure::Extensions,{} },
        { EInfrastructure::Instance,{ EInfrastructure::Functions, EInfrastructure::Layers, EInfrastructure::Extensions } },
        { EInfrastructure::DebugUtilsObject,{} },
        { EInfrastructure::Surface,{} },
        { EInfrastructure::PhysicalDevice,{} },
        { EInfrastructure::Device,{} },
        { EInfrastructure::GraphicQueue,{} },
        { EInfrastructure::PresentQueue,{} },
        { EInfrastructure::ComputeQueue,{} },
        { EInfrastructure::GraphicThreadQueue,{} },
        { EInfrastructure::ComputeThreadQueue,{} },
        { EInfrastructure::TransferThreadQueue,{} },
        { EInfrastructure::VideoEncodeThreadQueue,{} },
        { EInfrastructure::VideoDecodeThreadQueue,{} },
        { EInfrastructure::OpticalFlowThreadQueue,{} },
        { EInfrastructure::MemoryAllocator,{} },
        { EInfrastructure::SwapChain,{} },
        { EInfrastructure::GraphicTimeLine,{} },
        { EInfrastructure::ComputeTimeLine,{} },
        { EInfrastructure::GraphicImageSemaphore,{} },
        { EInfrastructure::GraphicQueueSemaphore,{} },
        { EInfrastructure::GraphicCommandPool,{} },
        { EInfrastructure::GraphicCommandBuffer,{} },
        { EInfrastructure::ComputeCommandPool,{} },
        { EInfrastructure::ComputeCommandBuffer,{} },
        { EInfrastructure::GraphicThreadCommandPool,{} },
        { EInfrastructure::ComputeThreadCommandPool,{} },
        { EInfrastructure::TransferThreadCommandPool,{} },
        { EInfrastructure::VideoEncodeThreadCommandPool,{} },
        { EInfrastructure::OpticalFlowThreadCommandPool,{} },
        { EInfrastructure::DescriptorPool,{} },
        { EInfrastructure::Middlewares,{} },
        { EInfrastructure::GarbageCollection,{} },
        { EInfrastructure::AccessibleInfrastructures,{} }
    }};
    
    static_assert(g.Execute());
}

#endif