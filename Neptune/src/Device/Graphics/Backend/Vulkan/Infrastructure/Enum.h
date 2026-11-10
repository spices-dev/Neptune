/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

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
        
        GarbageCollection,                   // @brief GarbageCollection.
        AccessibleInfrastructures,           // @brief AccessibleInfrastructures.

        Count
    };

}

#endif