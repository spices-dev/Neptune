/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

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
        AccessibleInfrastructures,           // @brief AccessibleInfrastructures.
        
        Count
    };

}

#endif